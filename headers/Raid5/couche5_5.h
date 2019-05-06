/// \file couche5_5.h
/// \brief header de la couche 5 raid 5
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef COUCHE5_5_H
#define COUCHE5_5_H
#define NBMOTSMAX 20


/* Dépendances */


#include "couche4_5.h"
#include <unistd.h>
#include <sys/wait.h>


/* Fonctions */
int Decoupe(char Chaine[], char *pMots[]);
void ls(char *commande[], int nbMot);
void cat(char *commande[], int nbMot);
void rm(char *commande[], int nbMot);
void load(char *commande[], int nbMot);
void store(char *commande[], int nbMot);
void create(char *commande[], int nbMot);
void edit(char *commande[], int nbMot);
void interpret();

#endif
