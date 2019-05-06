/// \file couche5_0.h
/// \brief header de la couche 5 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE5_0_H
#define COUCHE5_0_H


/* Dépendances */


#include "couche4_0.h"
#include "../Raid5/couche5_5.h"


/* Fonctions */
void r0_cat(char *commande[], int nbMot);
void r0_load(char *commande[], int nbMot);
void r0_create(char *commande[], int nbMot);
void r0_edit(char *commande[], int nbMot);
void r0_interpret();

#endif
