/// \file testunitaire.h
/// \brief header des tests unitaire
/// \author Guillaume Fourcroy
/// \date 27 avril 2019

#ifndef TESTUNITAIRE_H
#define TESTUNITAIRE_H

/* dépendances */

#include "../headers/Raid5/couche5_5.h"

/* Fonctions */

/* couche 1 */
void test_couche1(void);
void test_compute_nblock(FILE* file);
void test_write_block(FILE* file);
void test_read_block(FILE* file);
void test_affichage_couche1(FILE* file);
void test_block_repair(FILE* file);
/* couche 2 */
void test_couche2(void);
void test_compute_nstripe(FILE * file);
void test_compute_parity(FILE *file);
void test_compute_parity_index(FILE* file);
/* couche 3 */
void test_couche3(void);
void test_uchar_to_uint(FILE * file);
void test_uint_to_uchar(FILE * file);
void test_double_sens(FILE * file, uint valeur);
void dump_inode(FILE * file);
void test_inode(FILE *file);
/* couche 4 */
void test_couche4(void);

#endif
