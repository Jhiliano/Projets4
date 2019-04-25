/// \file main.c
/// \brief ficher main
/// \author Guillaume Fourcroy
/// \date 24 février 2019

/* dépendances */

#include "../headers/Raid5/couche1.h"
#include "../headers/Raid5/couche2.h"
#include "../headers/Raid5/couche3.h"
#include "../headers/Raid5/couche4.h"
#include "../headers/Raid5/couche5.h"

/* fonctions */

int main(void)
/// \brief Main
/// \return EXIT_SUCCESS le programme n'a pas eut d'encombre sinon il aurrai rencontré un exit(EXIT_FAILURE)
{
  init_disk_raid5("disk");

  /* C'est les tests de la couche 3, je savais pas où les faire donc j'ai fait ici xD Vous pouvez les supprimer si vous voulez. Mais ça marche ^^ */

  /*read_super_block();
  printf("SUPER BLOCK\nRaid = %d\nBlock used = %d\nFirst = %d\n\n", r5Disk.super_block.raid_type, r5Disk.super_block.nb_blocks_used, r5Disk.super_block.first_free_byte);
  read_inodes_table();
  cmd_dump_inode("rien");
  init_inode("test1", 10, 5);
  init_inode("test2", 10, 6);
  init_inode("test3", 13, 7);
  init_inode("test4", 20, 5);
  init_inode("test5", 31, 2);
  //cmd_dump_inode("rien");
  delete_inode(2);
  //cmd_dump_inode("rien");
  write_inodes_table();
  first_free_byte();
  printf("SUPER BLOCK\nRaid = %d\nBlock used = %d\nFirst = %d\n\n", r5Disk.super_block.raid_type, r5Disk.super_block.nb_blocks_used, r5Disk.super_block.first_free_byte);
  write_super_block();*/

  eteindre_disk_raid5();
  printf("%d\n",compute_nblock(50));

  return EXIT_SUCCESS;
}
