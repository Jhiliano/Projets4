/// \file couche2_0.h
/// \brief header de la couche 2 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE2_0_H
#define COUCHE2_0_H

/* Dépendances */


#include "couche1_0.h"
#include "../Raid5/couche2_5.h"


/* Fonctions */
int r0_compute_nstripe(int nb_blocks);
int r0_write_chunk(uchar* buffer, int size, int position, virtual_disk_t* raid);
int r0_read_stripe(stripe_t* stripe, int pos, virtual_disk_t *raid);
int r0_read_chunk(uchar* buffer, int size, int position, virtual_disk_t *raid);


#endif
