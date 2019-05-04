#include "../../headers/Raid5/couche2.h"


int repair_raid(int iddisk) {
  int err;
  int nbmax = compute_nblock(MAX_FILE_SIZE)/4;
  stripe_t tab;
  tab.nblocks= r5Disk.ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t));
  for (int s = 0; s < nbmax; s++) {

    if((err = read_stripe(&tab, s*tab.nblocks*BLOCK_SIZE, &r5Disk))) return err;
    block_repair(&r5Disk, iddisk, tab.stripe);
  }
  free(tab.stripe);
  return 0;
}

int main(int argc, char* argv[])  {
  struct stat inforep;
  int err;
  int iddisk;
  if (argc != 3) {
    fprintf(stderr, "nombre d'argument incorrect\n");
    fprintf(stderr, "Usage %s repertoire numDisk\n",argv[0]);
    return 2;
  }

  if (stat(argv[1],&inforep)) {
    fprintf(stderr, "erreur lors de l'ouverture du repertoire\n");
    fprintf(stderr, "Usage %s repertoire numDisk\n",argv[0]);
    return 3;
  }
  if (!S_ISDIR(inforep.st_mode))
  {
    fprintf(stderr, "il faut mettre le repertoire du raid\n");
    fprintf(stderr, "Usage %s repertoire numDisk\n",argv[0]);
    return 4;
  }
  iddisk = atoi(argv[2]);
  init_disk_raid5(argv[1]);
  if( iddisk >= r5Disk.ndisk || iddisk<0) {
    fprintf(stderr, "numero de disk incorrect\n");
    fprintf(stderr, "Usage %s repertoire numDisk\n",argv[0]);
    return 5;
  }
  err = repair_raid(iddisk);
  eteindre_disk_raid5();
  return err;
}
