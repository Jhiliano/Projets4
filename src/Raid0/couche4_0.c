/// \file couche4_0.c
/// \brief ficher de code couche4 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid01/couche4_01.h"

/* fonctions */

int r0_writefile(char* nomFich, file_t fich){
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
  printf("taille fichier : %d premier bit %d\n",fich.size, first_byte);
  if (r0_write_chunk(fich.data, fich.size, first_byte, &r5Disk)) return 2;// cas ou il y a une erreur de lecture
  r0_init_inode(nomFich, fich.size, first_byte);
  return 0;
}

int r0_read_file(char* nomFich, file_t* fich){
  /**
  * \brief lit un fichier dans le raid
  * \param[in] nomFich le nom du fichier
  * \param[out] fich la structure contenant la taille est la data du fichier qui est lu
  * \return 0 si tout s'est bien passé 1 si le fichier existe pas 2 en cas d'erreur de lecture
  */
  int idLecture;
  bool exist = filexist(nomFich, &idLecture);
  if(!exist) return 1;// cas ou il existe pas
  fich->size = r5Disk.inodes[idLecture].size;
  if (r0_read_chunk(fich->data, fich->size, r5Disk.inodes[idLecture].first_byte, &r5Disk)) return 2;// cas d'erreur de lecture

  return 0;
}


int r0_load_file_from_host(char* nomFich){
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
  return r0_writefile(nomFich, depotFich);
}
