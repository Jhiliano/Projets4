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
void test_couche3(void) {
  FILE* log = fopen("tests/logs/couche3.txt","w+");
  fprintf(log, "\nTEST COUCHE 3\n");
  fprintf(log, "\nTEST : char to uint \n\n");
  test_uchar_to_uint(log);
  fprintf(log, "\nTEST : uint to char \n\n");
  test_uint_to_uchar(log);
  fprintf(log, "\nTEST : conversion double sens \n\n");
  test_double_sens(log, 0);
  test_double_sens(log, 256425);
  test_double_sens(log, 4294967295);
  fprintf(log, "\nTEST : inode \n\n");
  test_inode(log);
  fclose(log);
}

void test_uchar_to_uint(FILE * file) {
  uchar* buffer = malloc(sizeof(uint));
  for(uint i = 0; i < sizeof(uint); i++) {
    buffer[i] = 255;
  }
  fprintf(file,"concaténation de uchar de valeur 255 : %ld\n",(long int) uchar_to_uint(buffer, 0));
}

void test_uint_to_uchar(FILE * file) {
  uchar* buffer = malloc(sizeof(uint));
  uint n = 42945;
  uint_to_uchar(buffer, 0, n);
  for(uint i = 0; i < sizeof(uint); i++) {
    fprintf(file,"%d ", (int)buffer[i]);
  }
  fprintf(file,"\n");
}

void test_double_sens(FILE * file, uint valeur) {
  uchar* buffer = malloc(sizeof(uint));
  uint_to_uchar(buffer, 0, valeur);
  fprintf(file ,"double conversion de %ld : %ld\n",(long int) valeur,(long int) uchar_to_uint(buffer, 0));
}

void test_inode(FILE *file) {
  fprintf(file,"\n\n\nSUPER BLOCK\nRaid = %d\nBlock used = %d\nFirst = %d\n\n", r5Disk.super_block.raid_type, r5Disk.super_block.nb_blocks_used, r5Disk.super_block.first_free_byte);
  dump_inode(file);
  init_inode("test1", 50, 800);
  init_inode("test2", 60, 200);
  init_inode("test3", 70, 350);
  init_inode("test4", 30, 150);
  init_inode("test5", 42, 230);
  fprintf(file,"\n\n\nSUPER BLOCK\nRaid = %d\nBlock used = %d\nFirst = %d\n\n", r5Disk.super_block.raid_type, r5Disk.super_block.nb_blocks_used, r5Disk.super_block.first_free_byte);
  dump_inode(file);
  delete_inode(2);
  fprintf(file,"\n\n\nSUPER BLOCK\nRaid = %d\nBlock used = %d\nFirst = %d\n\n", r5Disk.super_block.raid_type, r5Disk.super_block.nb_blocks_used, r5Disk.super_block.first_free_byte);
  dump_inode(file);
  delete_inode(0);
  delete_inode(1);
  delete_inode(4);
  delete_inode(3);
}

void dump_inode(FILE * file) {
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    if(r5Disk.inodes[i].first_byte) {
      fprintf(file,"Fichier %d : %s\nSize = %d\nNblock = %d\nFirst byte = %d\n\n****************************\n\n",i, r5Disk.inodes[i].filename, r5Disk.inodes[i].size, r5Disk.inodes[i].nblock, r5Disk.inodes[i].first_byte);
    }
  }
}
/* couche 4 */
void test_couche4(void) {
  FILE* log = fopen("tests/logs/couche4.txt","w+");
  fprintf(log, "\nTEST COUCHE 4\n");
  fprintf(log, "\nTEST : ecriture \n\n");
  fprintf(log, "lecture fichier 1 : code retour %d\n",  load_file_from_host("tests/in/image1.png"));
  fprintf(log, "lecture fichier 2 : code retour %d\n",  load_file_from_host("tests/in/image2.png"));
  fprintf(log, "lecture fichier 3 : code retour %d\n",  load_file_from_host("tests/in/text1.txt"));
  fprintf(log, "lecture fichier 3 : code retour %d\n",  load_file_from_host("tests/in/text2.txt"));
  fprintf(log, "lecture fichier 3 : code retour %d\n",  load_file_from_host("tests/in/text3.txt"));
  fprintf(log, "lecture fichier 3 : code retour %d\n",  load_file_from_host("tests/in/text4.txt"));
  fprintf(log, "lecture fichier 3 : code retour %d\n",  load_file_from_host("tests/in/compress.zip"));
  delete_inode(0);

  /*
  fprintf(log, "\nTEST : lecture \n\n");
  fprintf(log, "ecriture fichier 5 : code retour %d\n", store_file_to_host("tests/in/image1.png"));
  fprintf(log, "ecriture fichier 6 : code retour %d\n", store_file_to_host("tests/in/image2.png"));
  fprintf(log, "ecriture fichier 7 : code retour %d\n", store_file_to_host("tests/in/text.txt"));
  fprintf(log, "ecriture fichier 7 : code retour %d\n", store_file_to_host("tests/in/compress.zip"));
  fclose(log);
  */
}
/* main */
int main(void) {
  init_disk_raid5("disk/raid5");
  test_couche1();
  test_couche2();
  test_couche3();
  test_couche4();
  eteindre_disk_raid5();
  return 0;
}
