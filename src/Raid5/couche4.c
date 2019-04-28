/// \file couche4.c
/// \brief ficher de code couche4
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche4.h"

/* utilitaires */

bool filexist(char* nomFich, int* id) {
  /**
  * \brief Verifie si le fichier existe dans le raid
  * \param[in] nomFich le nom du fichier
  * \param[out] id l'id de l'innode ou il est stocké
  * \return 1 si il existe 0 sinon
  */
  for(int i=0; i<INODE_TABLE_SIZE; i++){
    if(strcmp(r5Disk.inodes[i].filename,nomFich)){
      *id=i;
      return 1;
    }
  }
  return 0;
}

/* fonctions */

int writefile(char* nomFich, file_t fich){
  /**
  * \brief ecrit un fichier dans le Raid
  * \param[in] nomFich le nom du fichier
  * \param[in] fich la structure contenant la taille est la data du fichier
  * \return 0 si tout s'est bien passé 1 si il y plus de place 2 en cas d'erreur d'ecriture
  */
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
  if (write_chunk(fich.data, fich.size, first_byte, &r5Disk)) return 2;// cas ou il y a une erreur de lecture
  init_inode(nomFich, fich.size, first_byte);
  return 0;
}



int read_file(char* nomFich, file_t* fich){
  /**
  * \brief lit un fichier dans le raid
  * \param[in] nomFich le nom du fichier
  * \param[out] fich la structure contenant la taille est la data du fichier qui est lu
  * \return 0 si tout s'est bien passé 1 si le fichier existe pas 2 en cas d'erreur de lecture
  */
  int idLecture;
  bool exist = filexist(nomFich, &idLecture);
  if(!exist) return 1;// cas ou il existe pas
  if (read_chunk(fich->data, fich->size, r5Disk.inodes[idLecture].first_byte, &r5Disk)) return 2;// cas d'erreur de lecture
  fich->size = r5Disk.inodes[idLecture].size;
  return 0;
}



int delete_file(char* nomFich){
  /**
  * \brief supprime un fichier dans le raid
  * \param[in] nomFich le nom du fichier
  * \return 0 si tout s'est bien passé 1 si le fichier n'exsite pas
  */
  int idSuppression;
  bool exist = filexist(nomFich, &idSuppression);
  if(!exist) return 1;
  delete_inode(idSuppression);
  return 0;
}

int load_file_from_host(char* nomFich){
  /**
  * \brief lit un fichier du host est l'ecrit sur le raid
  * \param[in] nomFich le nom du fichier
  * \return 0 si tout s'est bien passé 1 si il y plus de place 2 en cas d'erreur d'ecriture 3 si il y a une erreur d'ouverture du fichier 4 si il y a une erreur de lecture du fichier
  */
  FILE* fichier = fopen(nomFich,"r");
  file_t depotFich;
  if(!fichier) return 3; // cas erreur d'ouverture
  depotFich.size = fread(depotFich.data,sizeof(uchar),MAX_FILE_SIZE,fichier);//lecture
  if(depotFich.size <= 0) return 4; // cas erreur de lecture du fichier
  fclose(fichier);
  return writefile(nomFich, depotFich);
}



int store_file_to_host(char* nomFich){
  /**
  * \brief lit un fichier sur le raid et l'ecrit sur le host
  * \param[in] nomFich le nom du fichier
  * \return 0 si tout s'est bien passé 1 si le fichier existe pas 2 en cas d'erreur de lecture 3 si il y a une erreur d'ouverture du fichier 4 si il y a une erreur d'ecriture du fichier
  */
  FILE* fichier = fopen(nomFich,"w");
  file_t depotFich;
  int erreur = read_file(nomFich, &depotFich);
  uint oLus;
  if(!fichier) return 3; // cas erreur d'ouverture
  if(erreur) return erreur;
  oLus = fwrite(depotFich.data,sizeof(uchar),depotFich.size,fichier);
  if(oLus != depotFich.size) return 4; // fichier pas entierement lus
  fclose(fichier);
  return 0;
}
