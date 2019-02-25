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

	r5Disk.ndisk = 0;
	rep = opendir(adresse);
	while ((elem = readdir(rep)) != NULL)
	{
		if (strcmp(elem->d_name,"..") && strcmp(elem->d_name,"."))
		{
			strcpy(cheminFichier,adresse);
			strcat(cheminFichier,"/");
			strcat(cheminFichier,elem->d_name);
			stat(cheminFichier, &infosFichier);
			if (!S_ISDIR(infosFichier.st_mode))
			{
			/*	r5Disk.storage[r5Disk.ndisk] = fopen(cheminFichier,"r+");
				if (r5Disk.storage[r5Disk.ndisk] == NULL) {
					fprintf(stderr,"ouverture du disque impossible");
				}*/
				r5Disk.ndisk++;

			}
		}
	}
	closedir(rep);
}
