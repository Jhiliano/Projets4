/// \file couche3_5.h
/// \brief header de la couche 3 raid 5
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE3_5_H
#define COUCHE3_5_H


/* Dépendances */

#include "couche2_5.h"


/* Fonctions */

int read_inodes_table(void);
int write_inodes_table(void);
void delete_inode(int pos);
int get_unused_inode(void);
void init_inode(char *nomF, uint taille, uint pos);
int write_super_block(void);
int read_super_block(void);
void first_free_byte(void);

/* utilitaires */

void uint_to_uchar(uchar* buffer, int pos, uint n);
uint uchar_to_uint(uchar* buffer, int pos);

#endif
