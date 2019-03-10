/// \file couche2.c
/// \brief ficher de code couche2
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche2.h"


/* fonctions */
int compute_nstripe(int nb_blocks){
  if (nb_blocks%r5Disk.ndisk == 0) return nb_blocks/r5Disk.ndisk;
  return nb_blocks/r5Disk.ndisk+1;
}

block_t compute_parity(stripe_t bande, int posP){
  int i;
  block_t parite = bande.stripe[0];
  for(i=1; i<bande.nblocks; i++){
    if(i!=posP){
      for(int e=0; e<BLOCK_SIZE; e++){
        parite.data[e]=parite.data[e]^bande.stripe[i].data[e];
      }
    }
  }
  return parite;
}

int compute_parity_index(int numBande){
  return (r5Disk.ndisk-1)-(numBande%r5Disk.ndisk);
}
