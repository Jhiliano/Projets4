/// \file couche1_0.c
/// \brief ficher de code couche1 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid01/couche1_01.h"


/* fonctions */

void r0_init_disk_raid5(char* adresse)
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
	r5Disk.raidmode = ZERO;
	read_super_block();// Chargement super block ou initialisation si les disques sont nouveau (voir createdisk)
	read_inodes_table(); // Chargement de la table d'inode
	if (!r5Disk.super_block.first_free_byte) r5Disk.super_block.raid_type = r5Disk.raidmode;// si il est vierge on initialise le raidtype
	r5Disk.number_of_files = get_unused_inode();
	r5Disk.number_of_files = (r5Disk.number_of_files == -1)?0:get_unused_inode();
	closedir(rep);
}
