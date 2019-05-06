/// \file couche5_5.c
/// \brief ficher de code couche5 raid 5
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche5_5.h"
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


/* fonctions */
int Decoupe(char Chaine[], char *pMots[]) {
  int nbMot = 0, len;
  char *cur = strtok(Chaine, " ");
  while (cur != NULL) {
    pMots[nbMot++] = cur;
    cur = strtok(NULL, " ");
  }
  len = strlen(pMots[nbMot - 1]);
  pMots[nbMot - 1][len - 1] = '\0';
  return nbMot;
}

void ls(char *commande[], int nbMot) {
  if (nbMot > 2 || (nbMot == 2 && strcmp(commande[1], "-l")))
    fprintf(stderr, "Usage : ls [-l]\n");
  for (int i = 0; i < r5Disk.number_of_files; i++) {
    printf("%s ", r5Disk.inodes[i].filename);
    if (nbMot == 2) printf("size=%d nblock=%d first_byte=%d\n", r5Disk.inodes[i].size, r5Disk.inodes[i].nblock, r5Disk.inodes[i].first_byte);
  }
  if (nbMot == 1) printf("\n");
}

void cat(char *commande[], int nbMot) {
  int id;
  file_t fich;
  if (nbMot != 2)
    fprintf(stderr, "Usage : cat <nom de fichier>\n");
  else if (!filexist(commande[1], &id))
    fprintf(stderr, "%s n'existe pas.\n", commande[1]);
  else {
    read_file(commande[1], &fich);
    printf("%s", fich.data);
  }
}

void rm(char *commande[], int nbMot) {
  int id;
  if (nbMot != 2)
    fprintf(stderr, "Usage : rm <nom de fichier>\n");
  else if (!filexist(commande[1], &id))
    fprintf(stderr, "%s n'existe pas.\n", commande[1]);
  else delete_file(commande[1]);
}

void load(char *commande[], int nbMot) {
  if (nbMot != 2)
    fprintf(stderr, "Usage : load <nom de fichier>\n");
  else load_file_from_host(commande[1]);
}

void store(char *commande[], int nbMot) {
  int id;
  if (nbMot != 2)
    fprintf(stderr, "Usage : store <nom de fichier>\n");
  else if (!filexist(commande[1], &id))
    fprintf(stderr, "%s n'existe pas.\n", commande[1]);
  else store_file_to_host(commande[1]);
}

void create(char *commande[], int nbMot) {
  if (nbMot != 2)
    fprintf(stderr, "Usage : store <nom de fichier>\n");
  else {
    file_t new;
    new.size = 0;
    writefile(commande[1], new);
  }
}

void edit(char *commande[], int nbMot) {
  int id;
  file_t fich;
  if (nbMot != 2)
    fprintf(stderr, "Usage : edit <nom de fichier>\n");
  else if (!filexist(commande[1], &id))
    fprintf(stderr, "%s n'existe pas.\n", commande[1]);
  else {
    read_file(commande[1], &fich);
    printf("%s :\n%s\n-> ", commande[1], fich.data);
    delete_file(commande[1]);
    if (fgets((char*)fich.data, FILENAME_MAX_SIZE, stdin)) writefile(commande[1], fich);
  }
}

void interpret(){

  char commande[FILENAME_MAX_SIZE*2];
  char* tCommande[NBMOTSMAX+1];
  int nbMot = 0;
  if (fgets(commande, FILENAME_MAX_SIZE*2, stdin)) nbMot = Decoupe(commande, tCommande);

  while(strcmp(tCommande[0], "quit")){

    if(!strcmp(tCommande[0], "ls")) ls(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "cat")) cat(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "rm")) rm(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "load")) load(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "store")) store(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "create")) create(tCommande, nbMot);
    else if(!strcmp(tCommande[0], "edit")) edit(tCommande, nbMot);
    else printf("Commande inconnue\n");

    if (fgets(commande, FILENAME_MAX_SIZE*2, stdin)) nbMot = Decoupe(commande, tCommande);
  }
}
