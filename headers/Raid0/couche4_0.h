/// \file couche4_0.h
/// \brief header de la couche 4 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE4_0_H
#define COUCHE4_0_H

/* Dépendances */

#include "couche3_0.h"
#include "../Raid5/couche4_5.h"

/* Définitions */
int r0_writefile(char* nomFich, file_t fich);
int r0_read_file(char* nomFich, file_t* fich);
int r0_load_file_from_host(char* nomFich);
/* utilitaires */

#endif
