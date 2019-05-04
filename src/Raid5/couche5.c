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
int Decoupe(char Chaine[], char *pMots[]) {
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


void interpret(){

  char commande[FILENAME_MAX_SIZE*2];
  char* tCommande[NBMOTSMAX+1];
  // pid_t pidF;
  if(scanf("%s", commande)!=0) exit(1);
  Decoupe(commande, tCommande);

  while(!(strcmp(tCommande[0], "quit"))){
    if(strcmp(tCommande[0], "ls") || strcmp(tCommande[0], "cat")) execvp(commande, tCommande);
    else if(strcmp(tCommande[0], "rm")) delete_file(tCommande[1]);
    else if(strcmp(tCommande[0], "load")) load_file_from_host(tCommande[1]);
    else if(strcmp(tCommande[0], "store")) store_file_to_host(tCommande[1]);
    else if(strcmp(tCommande[0], "create")){
      file_t nouv;
      writefile(tCommande[1], nouv);
    }

    else if(strcmp(tCommande[0], "edit")){
      /*pidF=fork();
      char* tab = {"launch_atom", tCommande[1], NULL};
    	switch(pidF){
    		case -1:	perror("Echec fork\n");
    					    exit(1);
    		case 0:		execvp(tCommande[1], tab);
    		default:	wait(NULL);
    	}*/
    }
    if(scanf("%s", commande)!=0) exit(1);
  }
}
