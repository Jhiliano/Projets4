/// \file couche1_01.h
/// \brief header de la couche 1 raid 01
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE1_01_H
#define COUCHE1_01_H


/* Dépendances */


#include "couche3_01.h"
#include "../Raid0/couche1_0.h"



/* Fonctions */
void r01_half_init_disk_raid5(char* adresse, virtual_disk_t* raid);
void r01_init_disk_raid5();
void r01_remplir_storage(char* cheminFichier, virtual_disk_t* raid);
void r01_half_eteindre_disk_raid5(virtual_disk_t* raid);
void r01_eteindre_disk_raid5();

#endif
