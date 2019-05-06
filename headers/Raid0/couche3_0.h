/// \file couche3_0.h
/// \brief header de la couche 3 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE3_0_H
#define COUCHE3_0_H


/* Dépendances */

#include "couche2_0.h"
#include "../Raid5/couche3_5.h"


/* Fonctions */
void r0_init_inode(char *nomF, uint taille, uint pos);
int r0_write_inodes_table(void);
int r0_write_super_block(void);
int r0_read_super_block(void);
int r0_read_inodes_table(void);


#endif
