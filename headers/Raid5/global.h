/// \file global.h
/// \brief headers global comportant les dépendances principales
/// \author Guillaume Fourcroy
/// \date 24 février 2019

#ifndef GLOBAL_H
#define GLOBAL_H


/* Dépendances */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


/* Definitions */


#define ERREUR -1
/// \def ERREUR
/// valeur de l'erreur

#define BLOCK_SIZE 4
/// \def BLOCK_SIZE
/// taille du bloc (default 4) en octets

#define FILENAME_MAX_SIZE 32
/// \def FILENAME_MAX_SIZE
/// taille du nom du fichier (default 32) en caractères

#define INODE_TABLE_SIZE 10
/// \def INODE_TABLE_SIZE
/// taille de l'inode (default 10) en uchar

#define MAX_FILE_SIZE (50*1024)
/// \def MAX_FILE_SIZE
/// taille max du fichier (default 50*1024), taille fixe = nb max de fichiers

#define MAX_MSG 1024
/// \def MAX_MSG
/// taille du message maximum en uchar

#define SUPER_BLOCK_SIZE 4
/// \def SUPER_BLOCK_SIZE
/// nombre de blocs avec parité

#define INODES_START SUPER_BLOCK_SIZE*BLOCK_SIZE+1
/// \def INODES_START
/// taille de l'inode en octets

#define INODE_SIZE 11
/// \def INODE_SIZE
// inodes en blocks avec parité

typedef unsigned int uint; // même taille que int
/// \typedef uint
/// meme taille que int

typedef unsigned char uchar;
/// \typedef uchar
/// meme taille que unisgned char : 8 bits = octet

enum raid {ZERO,UN,CINQ,ZERO_UN,UN_ZERO,CINQUANTE,CENT};
/// \enum raid
/// type de raid : existant 0,1,5,0-1,1-0,50,100


/* Structures */

typedef struct block_s{
/// \struct block_s
/// \brief structure d'un block
/// \var block_s::data
/// tableau d'octets : une case par octet
  uchar data[BLOCK_SIZE];
} block_t;

typedef struct inode_s{
/// \struct inode_s
/// \brief structure d'une inode
/// \var inode_s::filename
/// tableau contenant le nom du fichier (dont '\0')
/// \var inode_s::size
/// taille du fichier en octets
/// \var inode_s::nblock
/// nombre de block du fichier = (size+BLOCK_SIZE-1)/BLOCK_SIZE ?
/// \var inode_s::first_byte
/// nombre du block de depart sur le dique virtuel
  char filename[FILENAME_MAX_SIZE]; // dont '\0'
  uint size;
  uint nblock;
  uint first_byte;
} inode_t;

typedef inode_t inode_table_t[INODE_TABLE_SIZE];
/// \typedef inode_table_t
/// redefinit inode_t en inode_table_t : une table d'inode avec INODE_TABLE_SIZE une taille fixe

typedef struct super_block_s{
/// \struct super_block_s
/// \brief information du fichier
/// \var super_block_s::raid_type
/// type du raid utilisé
/// \var super_block_s::nb_blocks_used
/// block utilisé par le fichier
/// \var super_block_s::first_free_byte
/// premier octet libre
  enum raid raid_type;
  uint nb_blocks_used ;
  uint first_free_byte;
  } super_block_t;
/// \typedef super_block_t
/// redefinit virtual_disk_s en virtual_disk_t

typedef struct virtual_disk_s {
/// \struct virtual_disk_s
/// \brief type du disque virtuel
/// \var virtual_disk_s::number_of_files
/// nombre de fichiers
/// \var virtual_disk_s::super_block
/// superbock du fichier contenant les information sur le fichier
/// \var virtual_disk_s::inodes
/// tableau d'inodes
/// \var virtual_disk_s::ndisk
/// nb de disques
/// \var virtual_disk_s::raidmode
/// type du raid utilisé
/// \var virtual_disk_s::storage
/// disques du systeme : tab[NUMBER_OF_DISKS]
    int number_of_files;
    super_block_t super_block;
    inode_table_t inodes;
    int ndisk;
    enum raid raidmode;
    FILE **storage;
} virtual_disk_t;
/// \typedef virtual_disk_t
/// redefinit virtual_disk_s en virtual_disk_t

typedef struct stripe_s {
/// \struct stripe_s
/// \brief inclut le bloc de parité
/// \var stripe_s::nblocks
/// egal à NB_DISK : un bloc par disque
/// \var stripe_s::stripe
/// stripe[NB_DISK] les data
  int nblocks;
  block_t *stripe;
} stripe_t;
/// \typedef stripe_t
/// redefinit stripe_s en stripe_t

typedef struct file_s{
/// \struct file_s
/// \brief structure du fichier contenant sa taille et les données
/// \var file_s::size
/// taille du fichier
/// \var file_s::data
/// données du fichier
uint size;
uchar data [MAX_FILE_SIZE] ;
} file_t ;
/// \typedef file_t
/// redefinit file_s en file_t


/*Variables globales*/


virtual_disk_t r5Disk;

#endif
