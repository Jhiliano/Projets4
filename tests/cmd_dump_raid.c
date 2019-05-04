#include "../headers/Raid5/couche2.h"

int main(void) {
  init_disk_raid5("disk");
  int nbmax = compute_nstripe(compute_nblock(MAX_FILE_SIZE));
  stripe_t tab;
  tab.nblocks= r5Disk.ndisk;
  tab.stripe = malloc(tab.nblocks*sizeof(block_t));
  for (int s = 0; s < nbmax; s++) {
    read_stripe(&tab, s*tab.nblocks*BLOCK_SIZE, &r5Disk);
    printf("%d | %d[",s*tab.nblocks*BLOCK_SIZE,compute_parity_index(s+1));
    for (int b = 0; b < tab.nblocks; b++) {
      print_block(stdout, tab.stripe[b]);
    }
    printf("]\n");
  }
  free(tab.stripe);
  eteindre_disk_raid5();
  return 0;
}
