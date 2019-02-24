/// \file couche4.h
/// \brief header de la couche 4
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE4_H
#define COUCHE4_H

/* Dépendances */
#include "global.h"

/* Définitions */

typedef struct file_s{
/// \struct file_s
/// \brief structure du fichier contenant sa taille et les données
/// \var file_s::size
/// taille du fichier
/// \var file_s::data
/// données du fichier
uint size;
uchar data [MAX_FILE_SIZE] ;
} file_t ;
/// \typedef file_t
/// redefinit file_s en file_t

/* Fonctions */

#endif
