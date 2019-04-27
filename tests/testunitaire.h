/// \file testunitaire.h
/// \brief header des tests unitaire
/// \author Guillaume Fourcroy
/// \date 27 avril 2019

#ifndef TESTUNITAIRE_H
#define TESTUNITAIRE_H

/* dépendances */

#include "../headers/Raid5/couche1.h"
#include "../headers/Raid5/couche2.h"
#include "../headers/Raid5/couche3.h"
#include "../headers/Raid5/couche4.h"
#include "../headers/Raid5/couche5.h"

/* Fonctions */

/* couche 1 */
void test_couche1(void);
void test_compute_nblock(FILE* file);
void test_write_block(FILE* file);
void test_read_block(FILE* file);
void test_affichage_couche1(FILE* file);
void test_block_repair(FILE* file);
/* couche 2 */

#endif
