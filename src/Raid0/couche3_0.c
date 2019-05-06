/// \file couche3_0.c
/// \brief ficher de code couche3 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid01/couche3_01.h"


/* fonctions */

void r0_init_inode(char *nomF, uint taille, uint pos) {
  /**
  * \brief Initialise un inode à partir de son nom, sa taille et sa position.
  * \details Avant d'appeler init_inode il faut vérifier que nomF < FILENAME_MAX_SIZE.
  * \param nomF Nom du fichier.
  * \param taille Taille du fichier.
  * \param pos  Position sur le raid.
  */

  inode_t i; // Nouveau inode.
  int i_inode; // Position à laquelle insérer cet inode.
  i_inode = get_unused_inode();
  // On remplit l'inode.
  strcpy(i.filename, nomF);
  i.size = taille;
  i.nblock = r0_compute_nstripe(compute_nblock(taille))*4;
  i.first_byte = pos;

  // On place l'inode dans la table
  r5Disk.inodes[i_inode] = i;

  // Mise à jour le super block.
  r5Disk.super_block.nb_blocks_used += i.nblock;
  first_free_byte();
  // Mise à jour du Raid
  r5Disk.number_of_files += 1;
}


int r0_write_inodes_table(void) {
  /**
  * \brief Ecrit la table d'inode dans le raid.
  * \details Sauvegarde de la table d'inodes et du super block.
  * \return 0 si cela s'est bien passé 1 si il y a eut une erreur de lecture
  */
  uchar* buffer = malloc(sizeof(inode_t));
  for (uint i = 0; i < INODE_TABLE_SIZE; i++) {// on fait l'operation suivante pour chaque inode
    for (uint c = 0; c < FILENAME_MAX_SIZE; c++) {// on ecrit les FILENAME_MAX_SIZE premiers octets qui représente le nom
       buffer[c] = r5Disk.inodes[i].filename[c];
    }
    uint_to_uchar(buffer, FILENAME_MAX_SIZE, r5Disk.inodes[i].size);// on converti et rentre les 3 uint apres FILENAME_MAX_SIZE
    uint_to_uchar(buffer, FILENAME_MAX_SIZE + sizeof(uint), r5Disk.inodes[i].nblock);
    uint_to_uchar(buffer, FILENAME_MAX_SIZE + sizeof(uint)*2, r5Disk.inodes[i].first_byte);
    if(r0_write_chunk(buffer, sizeof(inode_t), INODES_START+INODE_SIZE*i*BLOCK_SIZE-1, &r5Disk)) return 1;// on ecrit dans les disques et on verifie que tout s'est bien passé
  }
  free(buffer);
  return 0;
}


int r0_write_super_block(void) {
  /**
  * \brief Ecrit le super block au début du raid.
  * \return 1 si il u a eut une erreur 0 sinon.
  */
  uchar* buffer = malloc(sizeof(super_block_t));
  uint_to_uchar(buffer, 0, r5Disk.super_block.raid_type);// on converti et rentre les 3 uint de la structure et on les palce dans le buffer
  uint_to_uchar(buffer, sizeof(int), r5Disk.super_block.nb_blocks_used);
  uint_to_uchar(buffer, sizeof(int)*2, r5Disk.super_block.first_free_byte);
  if(r0_write_chunk(buffer, SUPER_BLOCK_SIZE*BLOCK_SIZE, 0, &r5Disk)) return 1;// on ecrit le buffer dans les disques et on verifie que tout s'est bien passé
  free(buffer);
  return 0;
}


int r0_read_super_block(void) {
  /**
  * \brief Lecture du super block.
  * \details fread stocke lit le super block au début du raid et le stocke dans r5Disk.super_block.
  * \return 0 si la lecture c'est bien passé, ERR_READ sinon.
  */
  uchar* buffer = malloc(sizeof(super_block_t));
  if(r0_read_chunk(buffer, SUPER_BLOCK_SIZE*BLOCK_SIZE, 0, &r5Disk)) return ERR_READ;
  r5Disk.super_block.raid_type = uchar_to_uint(buffer, 0);// on converti les uchar en int;
  r5Disk.super_block.nb_blocks_used = uchar_to_uint(buffer, sizeof(uint));
  r5Disk.super_block.first_free_byte = uchar_to_uint(buffer, sizeof(uint)*2);
  if(r5Disk.super_block.first_free_byte == 0) r5Disk.super_block.first_free_byte = INODES_START + INODE_SIZE*INODE_TABLE_SIZE*BLOCK_SIZE;
  free(buffer);
  return 0;
}


int r0_read_inodes_table(void) {
  /**
  * \brief Lit la table d'inode dans le raid.
  * \details Chargement de la table d'inodes et du super block.
  * \return 0 si tout c'est bien passé, ERR_READ si il a eu un problème de lecture.
  */
  uchar* buffer = malloc(sizeof(inode_t));
  for (uint i = 0; i < INODE_TABLE_SIZE; i++) {// on fait l'operation suivante pour chaque inode
    if(r0_read_chunk(buffer, sizeof(inode_t), INODES_START+i*INODE_SIZE*BLOCK_SIZE-1, &r5Disk)) return ERR_READ;// on recupere le tableau d'entiers représentant l'inode et on verifie que tout s'est bien passé
    for (uint c = 0; c < FILENAME_MAX_SIZE; c++) {// on recupère les FILENAME_MAX_SIZE premiers octets qui représente le nom
      r5Disk.inodes[i].filename[c] = buffer[c];
    }
    r5Disk.inodes[i].size = uchar_to_uint(buffer, FILENAME_MAX_SIZE);// on converti les uchar apres FILENAME_MAX_SIZE en int;
    r5Disk.inodes[i].nblock = uchar_to_uint(buffer, FILENAME_MAX_SIZE + sizeof(uint));
    r5Disk.inodes[i].first_byte = uchar_to_uint(buffer, FILENAME_MAX_SIZE + sizeof(uint)*2);
  }
  free(buffer);
  return 0;

}
