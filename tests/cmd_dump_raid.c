#include "../headers/Raid5/couche2.h"


int dump_raid(void) {
  int err;
  int nbmax = compute_nblock(MAX_FILE_SIZE)/4;
  stripe_t tab;
  tab.nblocks= r5Disk.ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t));
  for (int s = 0; s < nbmax; s++) {
    if((err = read_stripe(&tab, s*tab.nblocks*BLOCK_SIZE, &r5Disk))) return err;
    printf("%d %d | %d[",s,s*tab.nblocks*BLOCK_SIZE,compute_parity_index(s+1));
    for (int b = 0; b < tab.nblocks; b++) {
      print_block(stdout, tab.stripe[b]);
    }
    printf("]\n");
  }
  free(tab.stripe);
  return 0;
}

int main(int argc, char* argv[]) {
  struct stat inforep;
  if (argc != 2) return 2;
  if (stat(argv[1],&inforep)) return 3;
  if (!S_ISDIR(inforep.st_mode)) return 4;
  int err;
  init_disk_raid5(argv[1]);
  err = dump_raid();
  eteindre_disk_raid5();
  return err;
}
