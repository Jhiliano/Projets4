/// \file couche4.c
/// \brief ficher de code couche4
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid50/couche4_50.h"

/* utilitaires */
/**
bool filexist(char* nomFich, int* id) {
  for(int i=0; i<INODE_TABLE_SIZE; i++){
    if (r5Disk.inodes[i].first_byte) {
      if(!strcmp(r5Disk.inodes[i].filename,nomFich)){
        *id=i;
        return 1;
      }
    }
  }
  return 0;
}
**/
/* fonctions */
/**
int writefile(char* nomFich, file_t fich){
  int idEcriture;// l'id de la postion ou il faut ecrire le fichier
  bool exist = filexist(nomFich, &idEcriture);
  int first_byte;
  if(!exist){// cas ou il existe pas
    idEcriture = get_unused_inode();
    first_byte = r5Disk.super_block.first_free_byte;
  } else{
    if(fich.size<=r5Disk.inodes[idEcriture].size){// cas ou il est plus petit
      first_byte = r5Disk.inodes[idEcriture].first_byte;
    } else{// cas ou il est plus grand
      delete_inode(idEcriture);
      idEcriture = get_unused_inode();
      first_byte = r5Disk.super_block.first_free_byte;
    }
  }
  if (idEcriture == -1) return 1;// cas ou il y a pas de place
  printf("taille fichier : %d premier bit %d\n",fich.size, first_byte);
  if (write_chunk(fich.data, fich.size, first_byte, &r5Disk)) return 2;// cas ou il y a une erreur de lecture
  init_inode(nomFich, fich.size, first_byte);
  return 0;
}



int read_file(char* nomFich, file_t* fich){
  int idLecture;
  bool exist = filexist(nomFich, &idLecture);
  if(!exist) return 1;// cas ou il existe pas
  fich->size = r5Disk.inodes[idLecture].size;
  if (read_chunk(fich->data, fich->size, r5Disk.inodes[idLecture].first_byte, &r5Disk)) return 2;// cas d'erreur de lecture

  return 0;
}



int delete_file(char* nomFich){
  int idSuppression;
  bool exist = filexist(nomFich, &idSuppression);
  if(!exist) return 1;
  delete_inode(idSuppression);
  return 0;
}

int load_file_from_host(char* nomFich){
  FILE* fichier = fopen(nomFich,"r");
  file_t depotFich;
  if(!fichier) return 3; // cas erreur d'ouverture
  depotFich.size = fread(depotFich.data,sizeof(uchar),MAX_FILE_SIZE,fichier);//lecture
  if(depotFich.size <= 0) return 4; // cas erreur de lecture du fichier
  fclose(fichier);
  return writefile(nomFich, depotFich);
}



int store_file_to_host(char* nomFich){
  FILE* fichier;
  file_t depotFich;
  int erreur = read_file(nomFich, &depotFich);
  if(erreur) return erreur;
  fichier = fopen(nomFich,"w");
  uint oLus;
  if(!fichier) return 3; // cas erreur d'ouverture
  oLus = fwrite(depotFich.data,sizeof(uchar),depotFich.size,fichier);
  if(oLus != depotFich.size) return 4; // fichier pas entierement lus
  fclose(fichier);
  return 0;
}
*/
