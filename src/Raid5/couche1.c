/// \file couche1.c
/// \brief ficher de code couche1
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche1.h"


/* fonctions */
void init_disk_raid5(char* adresse){
	DIR* rep;
	rep = opendir(adresse);
	
}