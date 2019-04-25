/// \file couche4.c
/// \brief ficher de code couche4
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche4.h"


/* fonctions */
void writefile(char* nomFich, file_t fich){
  int exist=0;
  int indAjout;
  for(int i=0; i<INODE_TABLE_SIZE; i++){
    if(r5Disk.inodes[i].filename == nomFich){
      exist=1;
      indAjout=i;
    }
  }
  if(exist==0){
    indAjout = get_unused_inode();
  }
  else{
    if(fich.size<=r5Disk.inodes[indAjout].size){
      fseek(r5Disk.storage[fichier], indAjout, SEEK_SET);
      fwrite(&r5Disk.inodes[indAjout], sizeof(struct inode_s), 1, r5Disk.storage[fichier]);
    }
    else{

    }
  }
}

int read_file(char* nomF, file_t fich){
  return 1;
}

int delete_file(char* nomF){
  return 1;
}

void load_file_from_host(char* nomFich){

}

void store_file_to_host(char* nomFich){

}
