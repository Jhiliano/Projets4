/// \file couche4.h
/// \brief header de la couche 4
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE4_H
#define COUCHE4_H

/* Dépendances */


#include "../global.h"


/* Définitions */


/* Fonctions */
void writefile(char* nomFich, file_t fich);
int read_file(char* nomF, file_t fich);
int delete_file(char* nomF);
void load_file_from_host(char* nomFich);
void store_file_to_host(char* nomFich);

#endif
