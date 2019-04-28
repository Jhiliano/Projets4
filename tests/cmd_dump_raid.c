#include "../headers/Raid5/couche2.h"

int main(void) {
  init_disk_raid5("disk");
  int err;
  int nbmax = compute_nstripe(compute_nblock(1024*50))*4;
  uchar * buffer = malloc(nbmax*sizeof(uchar));
  err = read_chunk(buffer, nbmax, 0, &r5Disk);
  if(err) return 0;
  for (int c = 0; c < nbmax; c++) {
    printf("%02X ",buffer[c]);
  }
  printf("%d",err);
  free(buffer);
  eteindre_disk_raid5();
  return 0;
}
