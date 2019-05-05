/// \file couche1.h
/// \brief header de la couche 1
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE1_H
#define COUCHE1_H


/* Dépendances */


#include "../global.h"
#include "couche3_50.h"



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
