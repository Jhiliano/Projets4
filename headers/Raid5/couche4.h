/// \file couche4.h
/// \brief header de la couche 4
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE4_H
#define COUCHE4_H

/* Dépendances */


#include "../global.h"
#include "couche3.h"


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
