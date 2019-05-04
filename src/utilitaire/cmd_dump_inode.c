#include "../../headers/Raid5/couche3.h"

int main(int argc, char const *argv[]) {
  DIR* rep;
  int i = 0;
  if (argc != 2) {
    fprintf(stderr, "Nom du repertoire du raid requis\n");
    fprintf(stderr, "usage : %s Repertoire\n",argv[0] );
    return 1;
  }
  rep = opendir(argv[1]);
  if (rep  == NULL) {
    fprintf(stderr, "Nom du repertoire invalide\n");
    fprintf(stderr, "usage  :%s Repertoire\n",argv[0] );
    return 2;
  }
  init_disk_raid5("disk");
  printf("SUPER BLOCK\nRaid = %d\nBlock used = %d\nFirst = %d\n\nINODES\n", r5Disk.super_block.raid_type, r5Disk.super_block.nb_blocks_used, r5Disk.super_block.first_free_byte);
  while (i < INODE_TABLE_SIZE && r5Disk.inodes[i].first_byte) {
    printf("|Inode n°%d| Nom : %s / Taille : %d / Nombre block utilisé : %d / Premier byte utilisé %d\n",i,r5Disk.inodes[i].filename,r5Disk.inodes[i].size,r5Disk.inodes[i].nblock,r5Disk.inodes[i].first_byte);
    i++;
  }
  eteindre_disk_raid5();

  return 0;
}
