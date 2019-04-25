/// \file couche3.c
/// \brief ficher de code couche3
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche3.h"


/* fonctions */

void read_inodes_table() {

}

void write_inodes_table() {

}

void delete_inode(int pos) {
  /**
  * \brief Supprime un inode de la table.
  * \param pos  Position de l'inode à supprimer.
  */

  // Position du premier inode disponible dans le tableau.
  int i_inode;

  // Si il n'y a pas d'inode disponible on va à la fin du tableau.
  if ((i_inode = get_unused_inode()) == -1)
    i_inode = INODE_TABLE_SIZE - 1;

  // On décale les inodes en arrière à partir de l'inode à supprimer.
  for (int i = pos; i < i_inode - 1; i++)
    r5Disk.inodes[i] = r5Disk.inodes[i + 1];

  // On supprime le dernier inode pour ne pas l'avoir en double
  r5Disk.inodes[i_inode].first_byte = 0;
}

int get_unused_inode() {
  /**
  * \brief Renvoie la position du premier inode disponible.
  * \details Si il n'y a pas d'inode disponible on renvoie -1.
  * \return Un int correspondant à la position.
  */

  // Si le first byte = 0 alos l'inode est disponible.
  for (int i = 0; i < INODE_TABLE_SIZE; i++)
    if (r5Disk.inodes[i].first_byte == 0) return i;
  return -1;
}

int init_inode(char *nomF, uint taille, uint pos) {
  /**
  * \brief Initialise un inode à partir de son nom, sa taille et sa position.
  * \details Avant d'appeler init_inode il faut vérifier que nomF < FILENAME_MAX_SIZE.
  * \param nomF Nom du fichier.
  * \param taille Taille du fichier.
  * \param pos  Position sur le raid.
  * \return 0 si l'inode a été initialisé, 1 sinon.
  */

  inode_t i;
  int i_inode;

  // On vérifie qu'il y a de la place pour un inode.
  if ((i_inode = get_unused_inode()) != -1) {
    // On remplit l'inode.
    strcpy(i.filename, nomF);
    i.size = taille;
    i.nblock = compute_nblock(taille);
    i.first_byte = pos;
    // On place l'inode dans la table
    r5Disk.inodes[i_inode] = i;
    return 0;
  }

  return 1;
}

void cmd_dump_inode(char *nomR) {

}

void write_super_block() {

}

void read_super_block() {

}

void first_free_byte() {

}
