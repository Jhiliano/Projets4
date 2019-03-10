/// \file couche2.c
/// \brief ficher de code couche2
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche2.h"
#include "../../headers/Raid5/couche1.h"

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

int write_stripe(stripe_t bande, int pos){
  block_t parite;
  int indP = compute_parity_index(pos);
  int posParite = ((indP-1)*(BLOCK_SIZE*bande.nblocks))+1;
  int posOct = ((pos-1)*(BLOCK_SIZE*bande.nblocks))+1;

  for(int i=0; i<bande.nblocks; i++){
    if(i==indP){
      posOct+= BLOCK_SIZE;
    }
    write_block(posOct, r5Disk.storage[i], bande.stripe[i]);
    posOct+= BLOCK_SIZE;
  }
  parite = compute_parity(bande, pos);
  write_block(posParite, r5Disk.storage[indP], parite);
  return 0;
}

/*
int write_chunk(int n, uchar* buffer[]){
  for (int i = 0; i < n; i++){

  }
  return 0;
}*/
