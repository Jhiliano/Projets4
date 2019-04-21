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
  if (nb_blocks%r5Disk.ndisk-1 == 0) return nb_blocks/(r5Disk.ndisk-1);
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
    if (write_block(pos, r5Disk.storage[i], tab.stripe[i])!=BLOCK_SIZE) return 1;
  }
  return 0;
}
 void read_stripe(stripe_t* stripe, int posP, virtual_disk_t *raid){
   for (int i = 0;i < stripe->nblocks;i++) {
     read_block(posP, raid->storage[i], &stripe->stripe[i]);
   }
 }

 int write_chunk(uchar* buffer, int size, int position, virtual_disk_t* raid){
 	int nb = compute_nblock(size);
 	int nb_stripe = compute_nstripe(nb);
 	int ind_p;
 	stripe_t tab;
  tab.nblocks = raid->ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t));
 	int pos=0;
 	int test;

    int i =0;
    while(i<nb_stripe){

      tab.nblocks = raid->ndisk;
      tab.stripe = malloc(tab.nblocks*sizeof(block_t));
   		ind_p = compute_parity_index(i+1);

   		for(int id_block=0; id_block<tab.nblocks; id_block++){
        int num_b = 0;
   			if(num_b != ind_p-1){
            int num_o = 0;
            while(num_o < BLOCK_SIZE){
     					if(pos<size)
     						tab.stripe[num_b].data[num_o] = buffer[pos];
     					else
     						tab.stripe[num_b].data[num_o] = '0';
     					pos++;
              num_o ++ ;
   				}
   			}
   		}
   		compute_parity(raid, &tab, ind_p);
   		test = write_stripe(tab, position);

   		if(test != 0){
   			free(tab.stripe);
   			return 1;
   		}
   		position += BLOCK_SIZE;
      ++i;
 	}
 	free(tab.stripe);
 	return 0;
 }


 void read_chunk(uchar* buffer, int size, int position, virtual_disk_t *raid){
 	int nb = compute_nblock(size);
 	int nb_stripe = compute_nstripe(nb);
 	int id_p;
 	stripe_t tab;
 	int decalage=0;
 	int i=0;
  tab.nblocks = raid->ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t)); /*creation nouvelle bande*/
  while(i<nb_stripe){
    tab.nblocks = raid->ndisk;
    tab.stripe = malloc(tab.nblocks*sizeof(block_t));

 		id_p = compute_parity_index(i+1);
 		read_stripe(&tab, position, raid);
      int id = 0;
      while(id<tab.nblocks){
 			if(id != id_p-1){
          int o = 0;
          while(o<BLOCK_SIZE){
 					if(decalage<size)
 						buffer[decalage] = tab.stripe[id].data[o];
 					decalage++;
          o++;
 				}}
      id++;}
 		position = position + BLOCK_SIZE;
    ++i;
  }
 	free(tab.stripe);
 }
