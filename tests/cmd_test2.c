#include "../headers/Raid5/couche2.h"

int main(void) {
  init_disk_raid5("disk");
  int err;
  uchar * buffer = malloc(256*sizeof(uchar));
  err = read_chunk(buffer, 256, INODES_START + INODE_SIZE*INODE_TABLE_SIZE, &r5Disk);
  for (uchar c = 0; c < 255; c++) {
    printf("%02X ",buffer[c]);
  }
  printf("%02X ",buffer[255]);
  printf("\n");
  free(buffer);
  return err;
  eteindre_disk_raid5();
}
