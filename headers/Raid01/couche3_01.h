/// \file couche3_01.h
/// \brief header de la couche 3 raid 01
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE3_01_H
#define COUCHE3_01_H


/* Dépendances */

#include "couche2_01.h"
#include "../Raid0/couche3_0.h"

/* Fonctions */

int r01_read_super_block(virtual_disk_t raid);
int r01_read_inodes_table(virtual_disk_t raid);
int r01_write_super_block(virtual_disk_t raid);
int r01_write_inodes_table(virtual_disk_t raid);
void r01_delete_inode(int pos);

#endif
