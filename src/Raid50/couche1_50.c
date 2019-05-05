/// \file couche1.c
/// \brief ficher de code couche1
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid50/couche1_50.h"


/* fonctions */
/*
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
	r5Disk.raidmode = CINQ; //50
	read_super_block();// Chargement super block ou initialisation si les disques sont nouveau (voir createdisk)
	read_inodes_table(); // Chargement de la table d'inode
	if (!r5Disk.super_block.first_free_byte) r5Disk.super_block.raid_type = r5Disk.raidmode;// si il est vierge on initialise le raidtype
	r5Disk.number_of_files = get_unused_inode();
	r5Disk.number_of_files = (r5Disk.number_of_files == -1)?0:get_unused_inode();
	closedir(rep);
}
*/
/*---------------------FONCTION RAID50---------------*/
/*void init_disk_raid50(char* adresse1, char* adresse2){
	init_disk_raid5(adresse1);
	init_disk_raid5(adresse2);
}*/
/*
void remplir_storage(char* cheminFichier)
{
	r5Disk.storage = (FILE**) realloc(r5Disk.storage,(r5Disk.ndisk+1)*sizeof(FILE*));
	r5Disk.storage[r5Disk.ndisk] = fopen(cheminFichier,"r+");
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
	write_super_block(); // Sauvegarde du superblock
	write_inodes_table(); // Sauvegarde de la table d'inode
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
}

int write_block(int pos, FILE *disk, block_t block){
	if (fseek(disk, pos, SEEK_SET)!=0)return (0);
	 return (fwrite(block.data, sizeof(uchar), BLOCK_SIZE, disk));
}

int read_block(int pos, FILE *disk, block_t* block){
	if (fseek(disk, pos, SEEK_SET) != 0) return ERR_READ;
	if (fread(block->data, sizeof(uchar), BLOCK_SIZE, disk) < BLOCK_SIZE) return ERR_READ;
	return 0;
}

void block_repair(virtual_disk_t* raid, int block_id, block_t* stripe){
	block_t parite;// Block pour stocké les données des autres
	for (int i = 0; i < BLOCK_SIZE; i++) {
		parite.data[i] = 0;
	}
	for (int i = 0; i < raid->ndisk; i++){
		if (i != block_id-1){
			for (int e = 0; e < BLOCK_SIZE; e++){ // XOR sur chaque élément
				parite.data[e] = parite.data[e] ^ stripe[i].data[e];
			}
		}
	}
	for (int i = 0; i < BLOCK_SIZE; i++) {
		stripe[block_id-1].data[i] = parite.data[i];
	}
}

void print_block(FILE* file, block_t block) {
	for (int h = 0; h < BLOCK_SIZE; h++) {
		fprintf(file,"%02X",block.data[h]);
	}
	fprintf(file," ");
}
*/
