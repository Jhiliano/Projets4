/// \file couche3.c
/// \brief ficher de code couche3
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche3.h"


/* fonctions */

int read_inodes_table() {
  /**
  * \brief Lit la table d'inode dans le raid.
  * \return 0 si tout c'est bien passé, ERR_READ si il a eu un problème de lecture.
  */

  int pos = INODES_START; // Position de départ du tableau d'inodes dans le raid.
  int fichier; // fichier sur lequel lire un inode.

  // Parcours du tableau d'inodes.
  for (int i_inode = 0; i_inode < INODE_TABLE_SIZE; i_inode++) {
    fichier = i_inode % r5Disk.ndisk; // On se place dans le bon fichier.
    if (i_inode > 0 && fichier == 0) pos++; // Si on a lu dans tous les fichiers on incrémente pos.
    fseek(r5Disk.storage[fichier], pos, SEEK_SET); // Placer le curseur sur pos dans le bon fichier.
    if (fread(&r5Disk.inodes[i_inode], sizeof(struct inode_s), 1, r5Disk.storage[fichier]) != 1) return ERR_READ; // Lire l'inode.
  }

  return 0;
}

/*****************************************************************************************************************/

void write_inodes_table() {
  /**
  * \brief Ecrit la table d'inode dans le raid.
  */

  int pos = INODES_START; // Position de départ du tableau d'inodes dans le raid.
  int fichier; // fichier sur lequel écrire un inode.

  // Parcours du tableau d'inodes.
  for (int i_inode = 0; i_inode < INODE_TABLE_SIZE; i_inode++) {
    fichier = i_inode % r5Disk.ndisk; // On se place dans le bon fichier.
    if (i_inode > 0 && fichier == 0) pos++; // Si on a écrit dans tous les fichiers on incrémente pos.
    fseek(r5Disk.storage[fichier], pos, SEEK_SET); // Placer le curseur sur pos dans le bon fichier.
    fwrite(&r5Disk.inodes[i_inode], sizeof(struct inode_s), 1, r5Disk.storage[fichier]); // Ecrire l'inode.
  }
}

/*****************************************************************************************************************/

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

  // Mise à jour le super block.
  r5Disk.super_block.nb_blocks_used -= r5Disk.inodes[pos].nblock;

  // On décale les inodes en arrière à partir de l'inode à supprimer.
  for (int i = pos; i < i_inode - 1; i++)
    r5Disk.inodes[i] = r5Disk.inodes[i + 1];

  // On supprime le dernier inode pour ne pas l'avoir en double
  r5Disk.inodes[i_inode].first_byte = 0;
}

/*****************************************************************************************************************/

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

/*****************************************************************************************************************/

int init_inode(char *nomF, uint taille, uint pos) {
  /**
  * \brief Initialise un inode à partir de son nom, sa taille et sa position.
  * \details Avant d'appeler init_inode il faut vérifier que nomF < FILENAME_MAX_SIZE.
  * \param nomF Nom du fichier.
  * \param taille Taille du fichier.
  * \param pos  Position sur le raid.
  * \return 0 si l'inode a été initialisé, 1 sinon.
  */

  inode_t i; // Nouveau inode.
  int i_inode; // Position à laquelle insérer cet inode.

  // On vérifie qu'il y a de la place pour un inode.
  if ((i_inode = get_unused_inode()) != -1) {
    // On remplit l'inode.
    strcpy(i.filename, nomF);
    i.size = taille;
    i.nblock = compute_nblock(taille);
    i.first_byte = pos;

    // On place l'inode dans la table
    r5Disk.inodes[i_inode] = i;

    // Mise à jour le super block.
    r5Disk.super_block.nb_blocks_used += i.nblock;

    return 0;
  }

  return 1;
}

/*****************************************************************************************************************/

void cmd_dump_inode(char *nomR) {

}

/*****************************************************************************************************************/

int write_super_block() {
  /**
  * \brief Ecrit le super block au début du raid.
  * \return Le nombre d'élément écrit.
  */

  return (fwrite(&r5Disk.super_block, sizeof(struct super_block_s), 1, r5Disk.storage[1]));
}

/*****************************************************************************************************************/

int read_super_block() {
  /**
  * \brief Lecture du super block.
  * \details fread stocke lit le super block au début du raid et le stocke dans r5Disk.super_block.
  * \return 0 si la lecture c'est bien passé, ERR_READ sinon.
  */

  if (fread(&r5Disk.super_block, sizeof(struct super_block_s), 1, r5Disk.storage[1]) != 1) return ERR_READ;
	return 0;
}

/*****************************************************************************************************************/

void first_free_byte() {
  /**
  * \brief Mise à jour du premier byte libre.
  */

  int i_inode; // Position du premier inode disponible dans le tableau.

  // Si il n'y a pas d'inode disponible on va à la fin du tableau.
  if ((i_inode = get_unused_inode()) == -1)
    i_inode = INODE_TABLE_SIZE - 1;

  // Pour avoir le premier byte libre on prend le premier byte du dernier inode + la taille du fichier.
  r5Disk.super_block.first_free_byte = r5Disk.inodes[i_inode -1].first_byte + r5Disk.inodes[i_inode -1].size;
}
