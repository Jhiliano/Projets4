/// \file couche1_0.h
/// \brief header de la couche 1 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE1_0_H
#define COUCHE1_0_H


/* Dépendances */


#include "couche3_0.h"
#include "../Raid5/couche1_5.h"



/* Fonctions */

void r0_init_disk_raid5(char* adresse);

#endif
