/// \file couche1_5.h
/// \brief header de la couche 1 raid 5
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE1_5_H
#define COUCHE1_5_H


/* Dépendances */


#include "../global.h"
#include "couche3_5.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>



/* Fonctions */


void init_disk_raid5(char* adresse);
void remplir_storage(char* cheminFichier);
void creation_chemin_fichier(char *cheminFichier, const char* adresse, const char* nomFichier);
void eteindre_disk_raid5(void);

uint compute_nblock(uint n);

int write_block(int pos, FILE *disk, block_t block);
int read_block(int pos, FILE *disk, block_t* block);
void block_repair(virtual_disk_t *raid, int block_id, block_t* stripe);

void print_block(FILE* file, block_t block);
#endif
