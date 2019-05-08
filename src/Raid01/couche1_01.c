/// \file couche1_01.c
/// \brief ficher de code couche1 raid 01
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid01/couche1_01.h"


/* fonctions */
void r01_half_init_disk_raid5(char* adresse, virtual_disk_t* raid)
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
	raid->storage = (FILE**) malloc(0); // setup du tableau de fichier
	raid->ndisk = 0;
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
	raid->raidmode = ZERO;
	r01_read_super_block(*raid);// Chargement super block ou initialisation si les disques sont nouveau (voir createdisk)
	r01_read_inodes_table(*raid); // Chargement de la table d'inode
	if (!raid->super_block.first_free_byte) raid->super_block.raid_type = raid->raidmode;// si il est vierge on initialise le raidtype
	raid->number_of_files = get_unused_inode();
	raid->number_of_files = (raid->number_of_files == -1)?0:get_unused_inode();
	closedir(rep);
}

void r01_init_disk_raid5(char* adresse){
  r01_half_init_disk_raid5(adresse, &r01Disk.r0Disk1);
  r01_half_init_disk_raid5(adresse, &r01Disk.r0Disk2);
}

void r01_remplir_storage(char* cheminFichier, virtual_disk_t* raid)
{
	/**
	* \brief Remplit le raid 5 des fichiers
	* \details Remplit le champ storage de fichier et incrémente le compteur
	* \param cheminFichier Chemin du fichier placé dans le raid
	*/
	raid->storage = (FILE**) realloc(raid->storage,(raid->ndisk+1)*sizeof(FILE*));
	raid->storage[raid->ndisk] = fopen(cheminFichier,"r+");
	if ((raid->storage[raid->ndisk]) == NULL)
	{
		fprintf(stderr,"ouverture du fichier disque impossible");
	}
	raid->ndisk++;
}

void r01_half_eteindre_disk_raid5(virtual_disk_t* raid)
{
	/**
	* \brief Etein le raid 5
	* \details Sauvegarde la table d'inode et le superblock et free les fichier du raid 5
	*/
	r01_write_super_block(*raid); // Sauvegarde du superblock
	r01_write_inodes_table(*raid); // Sauvegarde de la table d'inode
	for (int i = 0; i < raid->ndisk;i++) {
		fclose(raid->storage[i]);//fermeture des fichiers ouverts
	}
	free(raid->storage);
}

void r01_eteindre_disk_raid5(){
  r01_half_eteindre_disk_raid5(&r01Disk.r0Disk1);
  r01_half_eteindre_disk_raid5(&r01Disk.r0Disk2);
}
