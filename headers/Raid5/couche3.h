/// \file couche3.h
/// \brief header de la couche 3
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE3_H
#define COUCHE3_H


/* Dépendances */


#include "global.h"
#include "couche1.h"


/* Fonctions */

void read_inodes_table();
void write_inodes_table();
void delete_inode(int pos);
int get_unused_inode();
int init_inode(char *nomF, uint taille, uint pos);
void cmd_dump_inode(char *nomR);
void write_super_block();
void read_super_block();
void first_free_byte();

#endif
