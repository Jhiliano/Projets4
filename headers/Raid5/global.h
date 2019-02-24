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

/* Definitions */

#define BLOCK_SIZE 4
/// \def BLOCK_SIZE
/// taille du bloc (default 4)

#define FILENAME_MAX_SIZE 32
/// \def FILENAME_MAX_SIZE
/// taille du nom du fichier (default 32)

#define INODE_TABLE_SIZE 10
/// \def INODE_TABLE_SIZE
/// taille de l'inode (default 10)

#define MAX_FILE_SIZE (50*1024)
/// \def MAX_FILE_SIZE
/// taille max du fichier (default 50*1024)

#endif
