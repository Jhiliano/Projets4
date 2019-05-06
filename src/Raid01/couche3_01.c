/// \file couche3_01.c
/// \brief ficher de code couche3 raid 01
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid01/couche3_01.h"


/* fonctions */

int r01_read_super_block(virtual_disk_t raid) {
  uchar* buffer = malloc(sizeof(super_block_t));
  if(r0_read_chunk(buffer, SUPER_BLOCK_SIZE*BLOCK_SIZE, 0, &raid)) return ERR_READ;
  raid.super_block.raid_type = uchar_to_uint(buffer, 0);// on converti les uchar en int;
  raid.super_block.nb_blocks_used = uchar_to_uint(buffer, sizeof(uint));
  raid.super_block.first_free_byte = uchar_to_uint(buffer, sizeof(uint)*2);
  if(raid.super_block.first_free_byte == 0) raid.super_block.first_free_byte = INODES_START + INODE_SIZE*INODE_TABLE_SIZE*BLOCK_SIZE;
  free(buffer);
  return 0;
}

int r01_read_inodes_table(virtual_disk_t raid) {
  uchar* buffer = malloc(sizeof(inode_t));
  for (uint i = 0; i < INODE_TABLE_SIZE; i++) {// on fait l'operation suivante pour chaque inode
    if(r0_read_chunk(buffer, sizeof(inode_t), INODES_START+i*INODE_SIZE*BLOCK_SIZE-1, &raid)) return ERR_READ;// on recupere le tableau d'entiers représentant l'inode et on verifie que tout s'est bien passé
    for (uint c = 0; c < FILENAME_MAX_SIZE; c++) {// on recupère les FILENAME_MAX_SIZE premiers octets qui représente le nom
      raid.inodes[i].filename[c] = buffer[c];
    }
    raid.inodes[i].size = uchar_to_uint(buffer, FILENAME_MAX_SIZE);// on converti les uchar apres FILENAME_MAX_SIZE en int;
    raid.inodes[i].nblock = uchar_to_uint(buffer, FILENAME_MAX_SIZE + sizeof(uint));
    raid.inodes[i].first_byte = uchar_to_uint(buffer, FILENAME_MAX_SIZE + sizeof(uint)*2);
  }
  free(buffer);
  return 0;
}

int r01_write_super_block(virtual_disk_t raid) {
  uchar* buffer = malloc(sizeof(super_block_t));
  uint_to_uchar(buffer, 0, raid.super_block.raid_type);// on converti et rentre les 3 uint de la structure et on les palce dans le buffer
  uint_to_uchar(buffer, sizeof(int), raid.super_block.nb_blocks_used);
  uint_to_uchar(buffer, sizeof(int)*2, raid.super_block.first_free_byte);
  if(r0_write_chunk(buffer, SUPER_BLOCK_SIZE*BLOCK_SIZE, 0, &raid)) return 1;// on ecrit le buffer dans les disques et on verifie que tout s'est bien passé
  free(buffer);
  return 0;
}

int r01_write_inodes_table(virtual_disk_t raid) {
  uchar* buffer = malloc(sizeof(inode_t));
  for (uint i = 0; i < INODE_TABLE_SIZE; i++) {// on fait l'operation suivante pour chaque inode
    for (uint c = 0; c < FILENAME_MAX_SIZE; c++) {// on ecrit les FILENAME_MAX_SIZE premiers octets qui représente le nom
       buffer[c] = raid.inodes[i].filename[c];
    }
    uint_to_uchar(buffer, FILENAME_MAX_SIZE, raid.inodes[i].size);// on converti et rentre les 3 uint apres FILENAME_MAX_SIZE
    uint_to_uchar(buffer, FILENAME_MAX_SIZE + sizeof(uint), raid.inodes[i].nblock);
    uint_to_uchar(buffer, FILENAME_MAX_SIZE + sizeof(uint)*2, raid.inodes[i].first_byte);
    if(r0_write_chunk(buffer, sizeof(inode_t), INODES_START+INODE_SIZE*i*BLOCK_SIZE-1, &raid)) return 1;// on ecrit dans les disques et on verifie que tout s'est bien passé
  }
  free(buffer);
  return 0;
}

void r01_delete_inode(int pos) {
  /**
  * \brief Supprime un inode de la table.
  * \param pos  Position de l'inode à supprimer.
  */

  // Position du premier inode disponible dans le tableau.
  int i_inode;

  // Si il n'y a pas d'inode disponible on va à la fin du tableau.
  if ((i_inode = get_unused_inode()) == -1)
    i_inode = INODE_TABLE_SIZE - 1;
  // Mise à jour du super block.
    r01Disk.r0Disk1.super_block.nb_blocks_used -= r01Disk.r0Disk1.inodes[pos].nblock;
    r01Disk.r0Disk2.super_block.nb_blocks_used -= r01Disk.r0Disk2.inodes[pos].nblock;
  // On décale les inodes en arrière à partir de l'inode à supprimer.
  for (int i = pos; i < i_inode - 1; i++) {
    r01Disk.r0Disk1.inodes[i] = r01Disk.r0Disk1.inodes[i + 1];
    r01Disk.r0Disk2.inodes[i] = r01Disk.r0Disk2.inodes[i + 1];
  }

  // On supprime le dernier inode pour ne pas l'avoir en double
  r01Disk.r0Disk1.inodes[i_inode - 1].first_byte = 0;
  r01Disk.r0Disk2.inodes[i_inode - 1].first_byte = 0;
  // Mise à jour du super block.
  first_free_byte();
  // Mise à jour du Raid
  r01Disk.r0Disk1.number_of_files -= 1;
  r01Disk.r0Disk2.number_of_files -= 1;
}
