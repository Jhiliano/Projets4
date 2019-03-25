/// \file couche2.h
/// \brief header de la couche 2
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE2_H
#define COUCHE2_H

/* Dépendances */


#include "global.h"


/* Fonctions */
int compute_nstripe(int nb_blocks);
void compute_parity(virtual_disk_t* raid, stripe_t* tab, int posP);
int compute_parity_index(int numBande);
int write_stripe(stripe_t bande, int pos);

#endif
