/// \file couche5_0.c
/// \brief ficher de code couche5 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid01/couche5_01.h"

/* fonctions */

void r0_cat(char *commande[], int nbMot) {
  int id;
  file_t fich;
  if (nbMot != 2)
    fprintf(stderr, "Usage : cat <nom de fichier>\n");
  else if (!filexist(commande[1], &id))
    fprintf(stderr, "%s n'existe pas.\n", commande[1]);
  else {
    r0_read_file(commande[1], &fich);
    printf("%s", fich.data);
  }
}


void r0_load(char *commande[], int nbMot) {
  if (nbMot != 2)
    fprintf(stderr, "Usage : load <nom de fichier>\n");
  else r0_load_file_from_host(commande[1]);
}


void r0_create(char *commande[], int nbMot) {
  if (nbMot != 2)
    fprintf(stderr, "Usage : store <nom de fichier>\n");
  else {
    file_t new;
    new.size = 0;
    r0_writefile(commande[1], new);
  }
}


void r0_edit(char *commande[], int nbMot) {
  int id;
  file_t fich;
  if (nbMot != 2)
    fprintf(stderr, "Usage : edit <nom de fichier>\n");
  else if (!filexist(commande[1], &id))
    fprintf(stderr, "%s n'existe pas.\n", commande[1]);
  else {
    r0_read_file(commande[1], &fich);
    printf("%s :\n%s\n-> ", commande[1], fich.data);
    delete_file(commande[1]);
    if (fgets((char*)fich.data, FILENAME_MAX_SIZE, stdin)) r0_writefile(commande[1], fich);
  }
}

void r0_interpret(){

  char commande[FILENAME_MAX_SIZE*2];
  char* tCommande[NBMOTSMAX+1];
  int nbMot = 0;
  if (fgets(commande, FILENAME_MAX_SIZE*2, stdin)) nbMot = Decoupe(commande, tCommande);

  while(strcmp(tCommande[0], "quit")){

    if(!strcmp(tCommande[0], "ls")) ls(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "cat")) r0_cat(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "rm")) rm(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "load")) r0_load(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "store")) store(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "create")) r0_create(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "edit")) r0_edit(tCommande, nbMot);
    else printf("Commande inconnue\n");

    if (fgets(commande, FILENAME_MAX_SIZE*2, stdin)) nbMot = Decoupe(commande, tCommande);
  }
}
