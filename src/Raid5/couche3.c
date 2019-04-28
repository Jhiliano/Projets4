/// \file couche3.c
/// \brief ficher de code couche3
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche3.h"


/* fonctions */

int read_inodes_table(void) {
  /**
  * \brief Lit la table d'inode dans le raid.
  * \details Chargement de la table d'inodes et du super block.
  * \return 0 si tout c'est bien passé, ERR_READ si il a eu un problème de lecture.
  */
  uchar* buffer = malloc(sizeof(inode_t));
  for (uint i = 0; i < INODE_TABLE_SIZE; i++) {// on fait l'operation suivante pour chaque inode
    if(read_chunk(buffer, sizeof(inode_t), INODES_START*BLOCK_SIZE+i*INODE_SIZE*BLOCK_SIZE, &r5Disk)) return ERR_READ;// on recupere le tableau d'entiers représentant l'inode et on verifie que tout s'est bien passé
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

/*****************************************************************************************************************/

int write_inodes_table(void) {
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
    if(write_chunk(buffer, sizeof(inode_t), INODES_START*BLOCK_SIZE+INODE_SIZE*i*BLOCK_SIZE, &r5Disk)) return 1;// on ecrit dans les disques et on verifie que tout s'est bien passé
  }
  free(buffer);
  return 0;
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
  // Mise à jour du super block.
    r5Disk.super_block.nb_blocks_used -= r5Disk.inodes[pos].nblock;
  // On décale les inodes en arrière à partir de l'inode à supprimer.
  for (int i = pos; i < i_inode - 1; i++)
    r5Disk.inodes[i] = r5Disk.inodes[i + 1];

  // On supprime le dernier inode pour ne pas l'avoir en double
  r5Disk.inodes[i_inode - 1].first_byte = 0;
  // Mise à jour du super block.
  first_free_byte();
  // Mise à jour du Raid
  r5Disk.number_of_files -= 1;
}

/*****************************************************************************************************************/

int get_unused_inode(void) {
  /**
  * \brief Renvoie la position du premier inode disponible.
  * \details Indique aussi si les innodes sont complet
  * \return Un int correspondant à la position, -1 si il y a plus de place
  */

  // Si le first byte = 0 alors l'inode est disponible.
  for (int i = 0; i < INODE_TABLE_SIZE; i++)
    if (r5Disk.inodes[i].first_byte == 0) return i;
  return -1;
}

/*****************************************************************************************************************/

void init_inode(char *nomF, uint taille, uint pos) {
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
  i.nblock = compute_nstripe(compute_nblock(taille))*4;
  i.first_byte = pos;

  // On place l'inode dans la table
  r5Disk.inodes[i_inode] = i;

  // Mise à jour le super block.
  r5Disk.super_block.nb_blocks_used += i.nblock;
  first_free_byte();
  // Mise à jour du Raid
  r5Disk.number_of_files += 1;
}


/*****************************************************************************************************************/

int write_super_block(void) {
  /**
  * \brief Ecrit le super block au début du raid.
  * \return 1 si il u a eut une erreur 0 sinon.
  */
  uchar* buffer = malloc(sizeof(super_block_t));
  uint_to_uchar(buffer, 0, r5Disk.super_block.raid_type);// on converti et rentre les 3 uint de la structure et on les palce dans le buffer
  uint_to_uchar(buffer, sizeof(int), r5Disk.super_block.nb_blocks_used);
  uint_to_uchar(buffer, sizeof(int)*2, r5Disk.super_block.first_free_byte);
  if(write_chunk(buffer, SUPER_BLOCK_SIZE*BLOCK_SIZE, 0, &r5Disk)) return 1;// on ecrit le buffer dans les disques et on verifie que tout s'est bien passé
  free(buffer);
  return 0;
}

/*****************************************************************************************************************/

int read_super_block(void) {
  /**
  * \brief Lecture du super block.
  * \details fread stocke lit le super block au début du raid et le stocke dans r5Disk.super_block.
  * \return 0 si la lecture c'est bien passé, ERR_READ sinon.
  */
  uchar* buffer = malloc(sizeof(super_block_t));
  if(read_chunk(buffer, SUPER_BLOCK_SIZE*BLOCK_SIZE, 0, &r5Disk)) return ERR_READ;
  r5Disk.super_block.raid_type = uchar_to_uint(buffer, 0);// on converti les uchar en int;
  r5Disk.super_block.nb_blocks_used = uchar_to_uint(buffer, sizeof(uint));
  r5Disk.super_block.first_free_byte = uchar_to_uint(buffer, sizeof(uint)*2);
  free(buffer);
  return 0;
}

/*****************************************************************************************************************/

void first_free_byte(void) {
  /**
  * \brief Mise à jour du premier byte libre.
  */

  uint size_inode = INODES_START*BLOCK_SIZE + INODE_SIZE*INODE_TABLE_SIZE*BLOCK_SIZE;// taille de la derniere inode du disque initialisé au premier bit utilisable du raid
  uint first_byte_inode = 0;// premier bit de la dernière inode
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    if(first_byte_inode < r5Disk.inodes[i].first_byte) {// on prend a chaque inode la dernière inode
      first_byte_inode = r5Disk.inodes[i].first_byte;
      size_inode = r5Disk.inodes[i].nblock*4;
    }
  }
  r5Disk.super_block.first_free_byte = first_byte_inode + size_inode;
}

/* utilitaire */

void uint_to_uchar(uchar* buffer, int pos, uint n) {
  /**
  * \brief Transformation d'un uint en uchar
  * \details Fait des decalages a droite pour recupérer les différent uchar
  * \param[out] buffer le tableau ou sera stocké les uchar
  * \param[in] pos la position dans le buffer ou stocker les uchar
  * \param[in] n l'uint a transformer
  */
  for(uint i = 0; i<sizeof(uint); i+=sizeof(uchar)) {
    buffer[pos+i] = n>>8*sizeof(uchar)*(sizeof(uint)-(i+1));// on prend d'abord les 8*sizeof(uint) bits a gauche et ensuite les suivant ect..
  }
}

uint uchar_to_uint(uchar* buffer, int pos) {
  /**
  * \brief Transformation d'un uchar en uint
  * \details Fait des decalages a gauche (pour etre symétrique a la fonction précédente) construisant l'int en plusieurs fois
  * \param[in] buffer le tableau ou est stocké les uchar
  * \param[in] pos la position dans le buffer ou stocker les uchar
  * \return l'uint construit a partir des uchar
  */
  uint n = 0;
  for(uint i = 0; i<sizeof(uint); i+=sizeof(uchar)) {
    n<<= 8*sizeof(uchar);// a chaque fois je fait des decalages a gauche pour mettre les précédents uchar entré dans l'int a gauche
    n += buffer[pos+i];// on ajour le uchar
  }
  return n;
}
