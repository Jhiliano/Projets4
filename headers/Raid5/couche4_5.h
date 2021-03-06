/// \file couche4_5.h
/// \brief header de la couche 4 raid 5
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE4_5_H
#define COUCHE4_5_H

/* Dépendances */

#include "couche3_5.h"


/* Définitions */

/* utilitaires */
bool filexist(char* nomFich, int* id);
/* Fonctions */
int writefile(char* nomFich, file_t fich);
int read_file(char* nomFich, file_t* fich);
int delete_file(char* nomFich);
int load_file_from_host(char* nomFich);
int store_file_to_host(char* nomFich);

#endif
