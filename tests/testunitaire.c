/// \file testunitaire.c
/// \brief ficher de code couche1
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "testunitaire.h"


/* fonctions */

/* couche 1 */

void test_couche1(void) {
  FILE* log = fopen("tests/logs/couche1.txt","w+");
  fprintf(log, "\nTEST COUCHE 1\n");
  fprintf(log, "\nTEST : compute block\n\n");
  test_compute_nblock(log);
  fprintf(log, "\nTEST : write block\n\n");
  test_write_block(log);
  fprintf(log, "\nTEST : read block\n\n");
  test_read_block(log);
  fprintf(log, "\nTEST : repair block\n\n");
  test_block_repair(log);
  fprintf(log, "\nTEST : print block\n\n");
  test_affichage_couche1(log);
  fclose(log);
}

void test_compute_nblock(FILE* file) {
  fprintf(file,"nb de block necessaire pour 0 octets : %d\n",compute_nblock(0));
  fprintf(file,"nb de block necessaire pour 1 octets : %d\n",compute_nblock(1));
  fprintf(file,"nb de block necessaire pour 4 octets : %d\n",compute_nblock(4));
  fprintf(file,"nb de block necessaire pour 5 octets : %d\n",compute_nblock(5));
  fprintf(file,"nb de block necessaire pour 50 octets : %d\n",compute_nblock(50));
}

void test_write_block(FILE* file) {
  block_t block1, block2;
  FILE* test = fopen("tests/filetest/c1","w+");
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block1.data[i] = 0;
    block2.data[i] = 255;
  }
  fprintf(file,"block composé de 0 ecrit en position 0 : bits ecrit = %d\n",write_block(0,test,block1));
  fprintf(file,"block composé de 255 ecrit en position 4 : bits ecrit = %d\n",write_block(4,test,block2));
  fclose(test);
}

void test_read_block(FILE* file) {
  block_t block1, block2;
  FILE* test = fopen("tests/filetest/c1","r");
  fprintf(file, "lecture du block composé de 1 en position 0 retour : %d block : ", read_block(0,test,&block1));
  print_block(file, block1);
  fprintf(file, "\n");
  fprintf(file, "lecture du block composé de 0 en position 4 retour : %d block : ", read_block(4,test,&block2));
  print_block(file, block2);
  fprintf(file, "\n");
  fclose(test);
}

void test_block_repair(FILE* file) {
  block_t stripe[r5Disk.ndisk];
  for (int d = 0; d < (r5Disk.ndisk)-1; d++) {
    for (int b = 0; b < BLOCK_SIZE; b++) {
      if (d == b) {
        stripe[d].data[b] = 255;
      } else {
        stripe[d].data[b] = 0;
      }
    }
  }
  fprintf(file, "creation des block de valeur : ");
  for (int d = 0; d < (r5Disk.ndisk)-1; d++) {
    print_block(file, stripe[d]);
  }
  block_repair(&r5Disk, 4, stripe);
  fprintf(file, "avec la creation du block 4 de parite : ");
  print_block(file, stripe[r5Disk.ndisk-1]);
  fprintf(file, "\n");
  stripe[0].data[0] = 0;
  fprintf(file, "modification du block 1 : ");
  for (int d = 0; d < (r5Disk.ndisk); d++) {
    print_block(file, stripe[d]);
  }
  fprintf(file, "\n");
  fprintf(file, "reparation du block 1 : ");
  block_repair(&r5Disk, 1, stripe);
  for (int d = 0; d < (r5Disk.ndisk); d++) {
    print_block(file, stripe[d]);
  }
  fprintf(file, "\n");
}

void test_affichage_couche1(FILE* file) {
  block_t block;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block.data[i] = 0;
  }
  fprintf(file, "block a 0 : ");
  print_block(file, block);
  fprintf(file, "\n");
  for (int i = 0; i < BLOCK_SIZE; i++) {
    block.data[i] = 255;
  }
  fprintf(file, "block avec des octets valeur 255 : ");
  print_block(file, block);
  fprintf(file, "\n");
}

/* couche 2 */

void test_couche2(void) {
  FILE* log = fopen("tests/logs/couche2.txt","w+");
  fprintf(log, "\nTEST COUCHE 2\n");
  fprintf(log, "\nTEST : compute stripe\n\n");
  test_compute_nstripe(log);
  fprintf(log, "\nTEST : compute parity\n\n");
  test_compute_parity(log);
  fprintf(log, "\nTEST : compute parity index\n\n");
  test_compute_parity_index(log);
  fclose(log);
}

void test_compute_nstripe(FILE * file) {
  fprintf(file,"stripe pour 0 block : %d\n",compute_nstripe(0));
  fprintf(file,"stripe pour 3 block : %d\n",compute_nstripe(3));
  fprintf(file,"stripe pour 4 block : %d\n",compute_nstripe(4));
  fprintf(file,"stripe pour 50 block : %d\n",compute_nstripe(50));
}

void test_compute_parity(FILE *file) {
  stripe_t stripe;
  stripe.stripe = malloc(r5Disk.ndisk*sizeof(block_t));
  for (int d = 0; d < (r5Disk.ndisk); d++) {
    if (d != 2) {
      for (int b = 0; b < BLOCK_SIZE; b++) {
        if (d == b) {
          stripe.stripe[d].data[b] = 0;
        } else {
          stripe.stripe[d].data[b] = 255;
        }
      }
    }
  }
  fprintf(file, "creation des block (sauf la 3e) de valeur : ");
  for (int d = 0; d < (r5Disk.ndisk); d++) {
    if (d != 2) {
      print_block(file, stripe.stripe[d]);
    }
  }
  fprintf(file, "\n");
  compute_parity(&r5Disk, &stripe, 3);
  fprintf(file, "la stripe a donc pour valeur :");
  for (int d = 0; d < (r5Disk.ndisk); d++) {
    print_block(file, stripe.stripe[d]);
  }
  fprintf(file, "\n");
  free(stripe.stripe);
}

void test_compute_parity_index(FILE* file) {
  for (int i =1 ; i <= 8; i++) {
      fprintf(file, "bande de parité de la stripe %d : %d\n",i,compute_parity_index(i));
  }
}

/* couche 3 */

/* couche 4 */

/* couche 5 */
