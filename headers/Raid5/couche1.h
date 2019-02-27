/// \file couche1.h
/// \brief header de la couche 1
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE1_H
#define COUCHE1_H


/* Dépendances */


#include "global.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>


/* Fonctions */


void init_disk_raid5(char* adresse);
void super_block_init(void);
void remplir_storage(char* cheminFichier);
void creation_chemin_fichier(char *cheminFichier, const char* adresse, const char* nomFichier);
void eteindre_disk_raid5(void);

uint compute_nblock(uint n);

void write_block(int pos, FILE *disk, block_t block);
int read_block(int pos, FILE *disk, block_t* block);

#endif
