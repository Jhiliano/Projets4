/// \file couche2.c
/// \brief ficher de code couche2
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche2.h"
#include "../../headers/Raid5/couche1.h"

/* fonctions */
int compute_nstripe(int nb_blocks){
  // une stipe peux contenir ndisk - 1 block car il doit tenir compte du block de parité
  if (nb_blocks%(r5Disk.ndisk-1) == 0) return nb_blocks/(r5Disk.ndisk-1);
  return nb_blocks/(r5Disk.ndisk-1)+1;
}


void compute_parity(virtual_disk_t* raid, stripe_t* tab, int posP){
  //meme methode pour la reparation et la création du block de parité.
  block_repair(raid, posP, tab->stripe);
}

int compute_parity_index(int numBande){
  //return (r5Disk.ndisk)-(numBande%r5Disk.ndisk)+1;
  return (r5Disk.ndisk)-((numBande-1)%r5Disk.ndisk);
}

int write_stripe(stripe_t tab, int pos){
  for(int i=0; i<tab.nblocks; i++){
    if (write_block(pos+i*BLOCK_SIZE, r5Disk.storage[i], tab.stripe[i])!=BLOCK_SIZE) return 1;
  }
  return 0;
}

int write_chunk(uchar* buffer, int size, int* position, virtual_disk_t* raid){
  // calculs des tailles block-stripe necessaire
 	int nb = compute_nblock(size);
 	int nb_stripe = compute_nstripe(nb);
 	int id_p; // id du block de parité
 	stripe_t tab;
  tab.nblocks = raid->ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t));
 	int pos = 0;
  for (int s = 0; s < nb_stripe; s++) {
   	id_p = compute_parity_index(s+1);
   	for (int id_block = 0; id_block < tab.nblocks; id_block++){
   		if (id_block != id_p-1){
        for (size_t num_o = 0; num_o < BLOCK_SIZE; num_o++) {
     			if(pos<size)
     				tab.stripe[id_block].data[num_o] = buffer[pos];
     			else
     				tab.stripe[id_block].data[num_o] = '0';
     		  pos++;
   			}
   		}
   	}
   	compute_parity(raid, &tab, id_p);
   	if(write_stripe(tab, *position) != 0){
   		free(tab.stripe);
   		return 1;
   	}
   	(*position) += BLOCK_SIZE*tab.nblocks;
 	}
 	free(tab.stripe);
 	return 0;
 }

int read_stripe(stripe_t* stripe, int pos, virtual_disk_t *raid){
  int erreur = -1;
  for (int i = 0;i < stripe->nblocks;i++) {
    if(read_block(pos+i*BLOCK_SIZE, raid->storage[i], &stripe->stripe[i])== ERR_READ) {
      if (erreur != -1)// on note l'erreur pour la reparer plus tard
        erreur = i;
      else
        return 1;//cas 2 erreurs => on sort
    }
  }
  if (erreur != -1) {// on repare l'erreur
    block_repair(raid, pos+erreur*BLOCK_SIZE, stripe->stripe);
    //write_stripe(*stripe, pos);// on le repare sur le disque
  }
  return 0;
}

int read_chunk(uchar* buffer, int size, int position, virtual_disk_t *raid){
  // calculs des tailles block-stripe necessaire
 	int nb = compute_nblock(size);
 	int nb_stripe = compute_nstripe(nb);
 	int id_p; // id du block de parité
 	stripe_t tab;
 	int decalage=0;
  tab.nblocks = raid->ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t)); /*creation nouvelle bande*/
  for (int s = 0; s < nb_stripe; s++) {
 		id_p = compute_parity_index(s+1);
 		if(read_stripe(&tab, position, raid)){// si il y a plus de 2 block illisible on stop
      free(tab.stripe);
      return 1;
    }
    for(int id_block = 0; id_block < tab.nblocks; id_block++) {
      if(id_block != id_p-1){
        for (int o = 0; o < BLOCK_SIZE; o++) {
 					if(decalage<size)
 						buffer[decalage] = tab.stripe[id_block].data[o];
 					decalage++;
 				}
      }
    }
 		position = position + BLOCK_SIZE*tab.nblocks;
  }
 	free(tab.stripe);
  return 0;
 }
