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
    fseek(r5Disk.storage[fichier], r5Disk.super_block.first_free_byte, SEEK_SET);
    fwrite(&r5Disk.inodes[indAjout], fich.size, 1, fich);
  }
  else{
    if(fich.size<=r5Disk.inodes[indAjout].size){
      fseek(r5Disk.storage[fichier], r5Disk.super_block.first_free_byte, SEEK_SET);
      fwrite(&r5Disk.inodes[indAjout], fich.size, 1, fich);
    }
    else{
      delete_inode(indAjout);
      indAjout = get_unused_inode();
      fseek(r5Disk.storage[fichier], r5Disk.super_block.first_free_byte, SEEK_SET);
      fwrite(&r5Disk.inodes[indAjout], fich.size, 1, fich);

    }
  }
}



int read_file(char* nomF, file_t fich){
  int indLecture;
  for(int i=0; i<INODE_TABLE_SIZE; i++){
    if(r5Disk.inodes[i].filename == nomFich){
      exist=1;
      indLecture=i;
    }
  }
  if(exist==0){
    return 0;
  }
  else{
    //fseek(r5Disk.inodes[indAjout], r5Disk.inodes[indLecture].first_byte , SEEK_SET);
    fread(r5Disk.inodes[indLecture], 1, r5Disk.inodes[indLecture].size, fich);
    return 1;
  }
}



int delete_file(char* nomF){
  int indSup;
  for(int i=0; i<INODE_TABLE_SIZE; i++){
    if(r5Disk.inodes[i].filename == nomFich){
      exist=1;
      indSup=i;
    }
  }
  if(exist==0){
    return 0;
  }
  else{
    delete_inode(indSup);
  }
}



void load_file_from_host(char* nomFich){
  stat* info;
  if(stat(nomFich, info)==0){
    int pos = get_unused_inode();
    init_inode(nomFich, (int)(infos->st_size), pos);
    fseek(r5Disk.inodes[pos], r5Disk.inodes[pos].first_byte, SEEK_SET); // Placer le curseur sur pos dans le bon fichier.
    fwrite(&r5Disk.inodes[pos], sizeof(struct inode_s), 1, nomFich); // Ecrire l'inode.
  }
}



void store_file_to_host(char* nomFich){

}
