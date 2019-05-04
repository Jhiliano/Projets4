#include "../../headers/Raid5/couche4.h"


int defrag_raid(void) {
  file_t file;
  int pos = INODES_START + INODE_SIZE*INODE_TABLE_SIZE*BLOCK_SIZE;
  for (int i = 0; i < INODE_TABLE_SIZE; i++) {
    if(r5Disk.inodes[i].first_byte) {
      file.size = r5Disk.inodes[i].size;
      if(read_chunk(file.data, file.size, pos, &r5Disk)) return 1;
      if(write_chunk(file.data, file.size, pos, &r5Disk)) return 1;
      r5Disk.inodes[i].first_byte = pos;
      pos+=r5Disk.inodes[i].nblock*BLOCK_SIZE;
    }
  }
  first_free_byte();
  return 0;
}

int main(int argc, char* argv[]) {
  struct stat inforep;
  if (argc != 2) {
    fprintf(stderr, "nombre d'argument incorrect");
    fprintf(stderr, "Usage %s repertoire",argv[0]);
    return 2;
  }

  if (stat(argv[1],&inforep)) {
    fprintf(stderr, "erreur lors de l'ouverture du repertoire");
    fprintf(stderr, "Usage %s repertoire",argv[0]);
    return 3;
  }
  if (!S_ISDIR(inforep.st_mode))
  {
    fprintf(stderr, "il faut mettre le repertoire du raid");
    fprintf(stderr, "Usage %s repertoire",argv[0]);
    return 4;
  }
  int err;
  init_disk_raid5(argv[1]);
  err = defrag_raid();
  eteindre_disk_raid5();
  return err;
}
