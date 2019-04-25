/// \file couche1.c
/// \brief ficher de code couche1
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche1.h"


/* fonctions */


void init_disk_raid5(char* adresse)
{
	DIR* rep;
	struct dirent* elem;
	struct stat infosFichier;
	char cheminFichier[66];
	r5Disk.storage = (FILE**) malloc(0); // setup du tableau de fichier
	r5Disk.ndisk = 0;
	rep = opendir(adresse);
	while ((elem = readdir(rep)) != NULL) // acces a tous les fichiers du rep
	{
		if (strcmp(elem->d_name,"..") && strcmp(elem->d_name,"."))
		{
			creation_chemin_fichier(cheminFichier, adresse, elem->d_name);// creation du chemin du fichier
			stat(cheminFichier, &infosFichier);
			if (!S_ISDIR(infosFichier.st_mode))
			{
				remplir_storage(cheminFichier);// remplissage du tableau de fichier
			}
		}
	}
	r5Disk.number_of_files = r5Disk.ndisk;// IDK j'ai l'impression que c'est la mm chose
	r5Disk.raidmode = CINQ;
	super_block_init();// setup du superblock
	closedir(rep);
}

void super_block_init(void)
{
	r5Disk.super_block.raid_type = r5Disk.raidmode;
	r5Disk.super_block.nb_blocks_used = 0;
	r5Disk.super_block.first_free_byte = 0;
}

void remplir_storage(char* cheminFichier)
{
	r5Disk.storage = (FILE**) realloc(r5Disk.storage,(r5Disk.ndisk+1)*sizeof(FILE*));
	r5Disk.storage[r5Disk.ndisk] = fopen(cheminFichier,"r+");
	/*Je sais pas pourquoi ce truc a été modifié mais ça marche pas donc j'ai remis la version qui marche*/
	/*r5Disk.storage = (FILE**) realloc(r5Disk.storage,(r5Disk.ndisk)*sizeof(FILE*));
	r5Disk.storage[r5Disk.ndisk-1] = fopen(cheminFichier,"r+");*/
	if ((r5Disk.storage[r5Disk.ndisk]) == NULL)
	{
		fprintf(stderr,"ouverture du fichier disque impossible");
	}
	r5Disk.ndisk++;
}

void creation_chemin_fichier(char *cheminFichier, const char* adresse, const char* nomFichier)
{
	strcpy(cheminFichier,adresse);
	strcat(cheminFichier,"/");
	strcat(cheminFichier,nomFichier);
}

void eteindre_disk_raid5(void)
{
	for (int i = 0; i < r5Disk.ndisk;i++) {
		fclose(r5Disk.storage[i]);//fermeture des fichiers ouverts
	}
	free(r5Disk.storage);
}

uint compute_nblock(uint n)
{
	if((n % BLOCK_SIZE)==0)
				return (n/BLOCK_SIZE);
	 return (n/BLOCK_SIZE+1);
	/*uint nBlockNecessaire = (n/BLOCK_SIZE+(n%BLOCK_SIZE != 0)); // division simple : un bloc vaut 4 octets (si cela n'est pas entier on rajoute un block)
	nBlockNecessaire = ((nBlockNecessaire*r5Disk.number_of_files)/(r5Disk.number_of_files-1)+((nBlockNecessaire*r5Disk.number_of_files)%(r5Disk.number_of_files-1) != 0)); // un block d'un fichier n'est pas utilisé : si c'est pas rond,on rajoute un block
	nBlockNecessaire += nBlockNecessaire%r5Disk.number_of_files; // on verifie qu'il y ait bien 4 block par fichiers utilisé
	return nBlockNecessaire;*/
}

/*ecrit un bloc block à pos sur disk*/
int write_block(int pos, FILE *disk, block_t block){
	if (fseek(disk, pos, SEEK_SET)==0)return (0);
	 return (fwrite(block.data, sizeof(uchar), BLOCK_SIZE, disk));

}

int read_block(int pos, FILE *disk, block_t* block){
	fseek(disk, pos, SEEK_SET);
	if (fread(block->data, sizeof(uchar), BLOCK_SIZE, disk) < BLOCK_SIZE) return ERR_READ;
	return 0;
}

int block_repair(virtual_disk_t *raid, int block_id, block_t* stripe){
	block_t parite;// Block pour stocké les données des autres
	int cond;
	//BUG pourquoi tu fait les deux condition qui suivent? tu ecris 2x le mm block dans la parite (le block 0 ou 1 sera ecrit 2x)
	if (block_id >1){
		for (int i = 0; i < BLOCK_SIZE; i++) {
			parite.data[i] = stripe[0].data[i];
			cond = 0;
		}}
		else {
			for (int i = 0; i < BLOCK_SIZE; i++) {
				parite.data[i] = stripe[1].data[i];
				cond = 1;
			}
	}
	for (int i = 0; i < raid->ndisk; i++){
		if (i != block_id-1 && i!=cond){
			for (int e = 0; e < BLOCK_SIZE; e++){ // XOR sur chaque élément
				parite.data[e] = parite.data[e] ^ stripe[i].data[e];
			}
		}
	}
	for (int i = 0; i < BLOCK_SIZE; i++) {
		stripe[block_id-1].data[i] = parite.data[i];

	}

	return 0;
}
