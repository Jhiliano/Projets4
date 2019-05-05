/// \file couche1.c
/// \brief ficher de code couche1
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche1.h"


/* fonctions */
/**
* \brief Ecrit la table d'inode dans le raid.
* \details Sauvegarde de la table d'inodes et du super block.
* \return 0 si cela s'est bien passé 1 si il y a eut une erreur de lecture
*/

void init_disk_raid5(char* adresse)
{
	/**
	* \brief Initialise le raid 5
	* \details Le raid 5 est initialisé en fonction d'un dossier entré en paramètre qui indique la position des disques
	* \param adresse Nom du dossier r5
	*/
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

/*---------------------FONCTION RAID50---------------*/
/*void init_disk_raid50(char* adresse1, char* adresse2){
	init_disk_raid5(adresse1);
	init_disk_raid5(adresse2);
}*/

void remplir_storage(char* cheminFichier)
{
	/**
	* \brief Remplit le raid 5 des fichiers
	* \details Remplit le champ storage de fichier et incrémente le compteur
	* \param cheminFichier Chemin du fichier placé dans le raid
	*/
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
	/**
	* \brief Crée le chemin du fichier
	* \param[out] cheminFichier Chemin du fichier placé dans le raid
	* \param[in] adresse Adresse du dossier
	* \param[in] nomFichier nom du fichier
	*/
	strcpy(cheminFichier,adresse);
	strcat(cheminFichier,"/");
	strcat(cheminFichier,nomFichier);
}

void eteindre_disk_raid5(void)
{
	/**
	* \brief Etein le raid 5
	* \details Sauvegarde la table d'inode et le superblock et free les fichier du raid 5
	*/
	write_super_block(); // Sauvegarde du superblock
	write_inodes_table(); // Sauvegarde de la table d'inode
	for (int i = 0; i < r5Disk.ndisk;i++) {
		fclose(r5Disk.storage[i]);//fermeture des fichiers ouverts
	}
	free(r5Disk.storage);
}

uint compute_nblock(uint n)
{
	/**
	* \brief Compte le nombre de block necessaire pour un nombre d'octets
	* \details Deux cas : le nombre d'octets rentre parfaitement ou le nombre d'octets demande un block de plus par rapport a sa division par BLOCK_SIZE
	* \param[in] n Un nombre d'octets
	* \return Un nombre de blocks
	*/
	if((n % BLOCK_SIZE)==0)
				return (n/BLOCK_SIZE);
	 return (n/BLOCK_SIZE+1);
}

int write_block(int pos, FILE *disk, block_t block){
	/**
	* \brief Ecriture d'un block
	* \details L'ecriture se fait a partir d'une position pos sur le fichier disk
	* \param[in] pos La position où ecrire
	* \param[in,out] disk Le disque à ecrire
	* \param[in] block Le block à ecrire
	* \return Le nombre d'octets ecrit
	*/
	if (fseek(disk, pos, SEEK_SET)!=0)return (0);
	 return (fwrite(block.data, sizeof(uchar), BLOCK_SIZE, disk));
}

int read_block(int pos, FILE *disk, block_t* block){
	/**
	* \brief Lecture d'un block
	* \details La lecture se fait a partir d'une position pos sur le fichier disk
	* \param[in] pos La position où lire
	* \param[in] disk Le disque à lire
	* \param[out] block Le block lu
	* \return 0 si tout se passe bien, ERR_READ sinon
	*/
	if (fseek(disk, pos, SEEK_SET) != 0) return ERR_READ;
	if (fread(block->data, sizeof(uchar), BLOCK_SIZE, disk) < BLOCK_SIZE) return ERR_READ;
	return 0;
}

void block_repair(virtual_disk_t* raid, int block_id, block_t* stripe){
	/**
	* \brief Reparation d'un block
	* \details effectue un XOR de chaque block pour recréer le block manquant
	* \param[in] raid Le raid
	* \param[in] block_id Le block à reparer
	* \param[in,out] stripe Un tableau de block
	* \return temoin erreurs
	*/
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
	/**
	* \brief Affichage d'un block
	* \details L'affichage est en hexadecimal, il affiche sur une ligne sans espace ni retour a ligne
	*/
	for (int h = 0; h < BLOCK_SIZE; h++) {
		fprintf(file,"%02X",block.data[h]);
	}
	fprintf(file," ");
}
