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
	uint nBlockNecessaire = (n/BLOCK_SIZE+(n%BLOCK_SIZE != 0)); // division simple : un block vaux 4 octets (si cela n'est pas entier on rajoute un block)
	nBlockNecessaire = ((nBlockNecessaire*r5Disk.number_of_files)/(r5Disk.number_of_files-1)+((nBlockNecessaire*r5Disk.number_of_files)%(r5Disk.number_of_files-1) != 0)); // un block d'un fichier n'est pas utilisé : si c'est pas rond,on rajoute un block
	nBlockNecessaire += nBlockNecessaire%r5Disk.number_of_files; // on verifie qu'il y ai bien 4 block par fichiers utilisé
	return nBlockNecessaire;
}

void write_block(int pos, virtual_disk_t disk){

}
