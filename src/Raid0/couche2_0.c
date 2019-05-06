/// \file couche2_0.c
/// \brief ficher de code couche2 raid 0
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid01/couche2_01.h"

/* fonctions */

int r0_compute_nstripe(int nb_blocks){
  /**
  * \brief Calcul le nombre de stripe pour un nombre de blocks
  * \param[in] nb_blocks Le nombre de block à calculer
  * \return Le nombre de stripe necessaire
  */
  if (nb_blocks%(r5Disk.ndisk) == 0) return nb_blocks/(r5Disk.ndisk);
  return nb_blocks/(r5Disk.ndisk)+1;
}

int r0_write_chunk(uchar* buffer, int size, int position, virtual_disk_t* raid){
  /**
  * \brief Ecrit un tableau de uchar sur le raid
  * \param[in] buffer Le buffer sur lequel il y a les uchar
  * \param[in] size Le nombre d'elements a ecrire
  * \param[in] position La position sur le raid ou ecrire
  * \param[in] raid Le raid
  * \return 0 si tout s'est bien passé 1 si il y a eut une erreur d'ecriture
  */
  // calculs des tailles block-stripe necessaire
  if(size == 0) return 0;
 	int nb = compute_nblock(size);
 	int nb_stripe = r0_compute_nstripe(nb);
 	stripe_t tab;
  tab.nblocks = raid->ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t));
 	int pos = 0;
  for (int s = 0; s < nb_stripe; s++) {// parcours de toutes les stripes a ecrire
   	for (int id_block = 0; id_block < tab.nblocks; id_block++){// parcours des block des stripes
      for (int num_o = 0; num_o < BLOCK_SIZE; num_o++) {// parcours des octets des stripes
  			if(pos<size) // gestion si le buffer ne rentre pas completement dans les stripes
  				tab.stripe[id_block].data[num_o] = buffer[pos];
  			else
  				tab.stripe[id_block].data[num_o] = '0';
  		  pos++;
  		}
   	}
   	if(write_stripe(tab, position,raid) != 0){ //on ecrit sur le Raid + gestion erreurs ecriture
   		free(tab.stripe);
   		return 1;
   	}
   	position += BLOCK_SIZE*tab.nblocks;//incrémentation de la longueur d'une stripe
 	}
 	free(tab.stripe);
 	return 0;
 }
