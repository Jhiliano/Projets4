#include "../headers/Raid5/couche2.h"

int main(void) {
  init_disk_raid5("disk");
  int err;
  uchar * buffer = malloc(256*sizeof(uchar));
  for (uchar c = 0; c < 255; c++) {
    buffer[c] = c;
  }
  buffer[255] = 255;
  err = write_chunk(buffer, 256, INODES_START + INODE_SIZE*INODE_TABLE_SIZE, &r5Disk);
  free(buffer);
  return err;
  eteindre_disk_raid5();
}
