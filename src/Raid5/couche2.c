/// \file couche2.c
/// \brief ficher de code couche2
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche2.h"

/* fonctions */
int compute_nstripe(int nb_blocks){
  /**
  * \brief Calcul le nombre de stripe pour un nombre de blocks
  * \details Une stipe peux contenir ndisk - 1 block car il doit tenir compte du block de parité
  * \param[in] nb_blocks Le nombre de block à calculer
  * \return Le nombre de stripe necessaire
  */
  if (nb_blocks%(r5Disk.ndisk-1) == 0) return nb_blocks/(r5Disk.ndisk-1);
  return nb_blocks/(r5Disk.ndisk-1)+1;
}


void compute_parity(virtual_disk_t* raid, stripe_t* tab, int posP){
  /**
  * \brief creer le block de parité dans une stripe
  * \details C'est la meme methode pour la reparation et la création du block de parité.
  * \param[in] raid Le Raid
  * \param[in] tab La stripe à compléter
  * \param[in] posP La position du block de parité
  */
  block_repair(raid, posP, tab->stripe);
}

int compute_parity_index(int numBande){
  /**
  * \brief Calcul de l'emplacement du block de parité sur le stripe
  * \details Calcul cyclique (4->1)
  * \param[in] numBande Le numero de la bande à calculer
  * \return L'emplacement du block de parité
  */
  return (r5Disk.ndisk)-((numBande-1)%r5Disk.ndisk);
}

int write_stripe(stripe_t stripe, int pos, virtual_disk_t* raid){
  /**
  * \brief Ecrit sur le raid la stripe
  * \details Utilise write block de la couche 1
  * \param[in] stripe La stripe a écrire
  * \param[in] pos La position ou ecrire la stripe
  * \param[in] raid Le raid
  * \return 0 si tout s'est bien passé 1 si il y a eut une erreur d'ecriture
  */
  for(int i = 0; i < stripe.nblocks; i++){
    if (write_block(pos+i*BLOCK_SIZE, raid->storage[i], stripe.stripe[i])!=BLOCK_SIZE) return 1;
  }
  return 0;
}

int write_chunk(uchar* buffer, int size, int position, virtual_disk_t* raid){
  /**
  * \brief Ecrit un tableau de uchar sur le raid
  * \details Créer les block de parité en appellant compute_parity
  * \param[in] buffer Le buffer sur lequel il y a les uchar
  * \param[in] size Le nombre d'elements a ecrire
  * \param[in] position La position sur le raid ou ecrire
  * \param[in] raid Le raid
  * \return 0 si tout s'est bien passé 1 si il y a eut une erreur d'ecriture
  */
  // calculs des tailles block-stripe necessaire
  if(size == 0) return 0;
 	int nb = compute_nblock(size);
 	int nb_stripe = compute_nstripe(nb);
 	int id_p; // id du block de parité
 	stripe_t tab;
  tab.nblocks = raid->ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t));
 	int pos = 0;
  for (int s = 0; s < nb_stripe; s++) {// parcours de toutes les stripes a ecrire
   	id_p = compute_parity_index(s+1);
   	for (int id_block = 0; id_block < tab.nblocks; id_block++){// parcours des block des stripes
   		if (id_block != id_p-1){
        for (int num_o = 0; num_o < BLOCK_SIZE; num_o++) {// parcours des octets des stripes
     			if(pos<size) // gestion si le buffer ne rentre pas completement dans les stripes
     				tab.stripe[id_block].data[num_o] = buffer[pos];
     			else
     				tab.stripe[id_block].data[num_o] = '0';
     		  pos++;
   			}
   		}
   	}
   	compute_parity(raid, &tab, id_p); // on fait le block de parité
   	if(write_stripe(tab, position,raid) != 0){ //on ecrit sur le Raid + gestion erreurs ecriture
   		free(tab.stripe);
   		return 1;
   	}
   	position += BLOCK_SIZE*tab.nblocks;//incrémentation de la longueur d'une stripe
 	}
 	free(tab.stripe);
 	return 0;
 }

int read_stripe(stripe_t* stripe, int pos, virtual_disk_t *raid){
  /**
  * \brief Lis une stripe sur le raid
  * \details Utilise read block de la couche 1
  * \param[out] stripe La stripe qui sera lu
  * \param[in] pos La position ou lire la stripe
  * \param[in] raid Le raid
  * \return 0 si tout s'est bien passé ERR_READ si il y a eut une erreur de lecture
  */
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
  /**
  * \brief Ecrit un tableau de uchar sur le raid
  * \details Créer les block de parité en appellant compute_parity
  * \param[out] buffer Le buffer sur lequel sera ecrit les données
  * \param[in] size Le nombre d'elements a lire
  * \param[in] position La position sur le raid ou lire
  * \param[in] raid Le raid
  * \return 0 si tout s'est bien passé 1 si il y a eut une erreur de lecture
  */
  // calculs des tailles block-stripe necessaire
 	int nb = compute_nblock(size);
 	int nb_stripe = compute_nstripe(nb);
 	int id_p; // id du block de parité
 	stripe_t tab;
 	int decalage=0;
  tab.nblocks = raid->ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t));
  for (int s = 0; s < nb_stripe; s++) { //parcours des stripes a lire
 		id_p = compute_parity_index(s+1);
 		if(read_stripe(&tab, position, raid)){// si il y a plus de 2 block illisible on stop
      free(tab.stripe);
      return 1;
    }
    for(int id_block = 0; id_block < tab.nblocks; id_block++) { //parcours des block des stripes
      if(id_block != id_p-1){
        for (int o = 0; o < BLOCK_SIZE; o++) {  //parcours des octets des block
 					if(decalage<size) // eviter de lire plus qu'on en a besoin
 						buffer[decalage] = tab.stripe[id_block].data[o];
 					decalage++;
 				}
      }
    }
 		position = position + BLOCK_SIZE*tab.nblocks;// incrementation de la taile d'une stripe
  }
 	free(tab.stripe);
  return 0;
 }
