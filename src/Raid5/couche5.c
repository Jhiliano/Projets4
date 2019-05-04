/// \file couche5.c
/// \brief ficher de code couche5
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche5.h"
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define NBMOTSMAX 20

/* fonctions */
int Decoupe(char Chaine[], char *pMots[])
{
  char *p;
  int NbMots=0;

  p=Chaine; /* On commence par le début */
  /* Tant que la fin de la chaîne n'est pas atteinte et qu'on ne déborde pas */
  while ((*p)!='\0' && NbMots<NBMOTSMAX)
  {
    while ((*p)==' ' && (*p)!='\0') p++; /* Recherche du début du mot */
    if ((*p)=='\0') break; /* Fin de chaîne atteinte */
    pMots[NbMots++]=p; /* Rangement de l'adresse du 1er caractère du mot */
    while ((*p)!=' ' && (*p)!='\0') p++; /* Recherche de la fin du mot */
    if ((*p)=='\0') break; /* Fin de chaîne atteinte */
    *p='\0'; /* Marquage de la fin du mot */
    p++; /* Passage au caractère suivant */
  }
  pMots[NbMots]=NULL; /* Dernière adresse */
  return NbMots;
}


void interpret(int argc, char*argv[]){
  char *pMots[NBMOTSMAX+1];
	pid_t pidF;
	int i =0;
	printf("> ");
	for(i=0; i<argc; i++){
		printf("%s ", argv[i]);
	}
	printf("\n");

	for(i=1; i<argc; i++){
		pidF=fork();
		switch(pidF){
			case -1:	perror("Echec fork\n");
						exit(1);
			case 0:	printf("[%d] Je lance %s :\n", (int)getpid(), argv[i]);
  						Decoupe(argv[i],pMots);
  						execvp(pMots[0],pMots);
  						perror(argv[i]);
  						exit(2);
			default: wait(NULL);
		}
	}
	printf(">\n");
}
