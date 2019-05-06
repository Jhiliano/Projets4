/// \file main.c
/// \brief ficher main
/// \author Guillaume Fourcroy
/// \date 24 février 2019

/* dépendances */

#include "../headers/Raid5/couche5_5.h"
#include "../headers/Raid0/couche5_0.h"
#include "../headers/Raid01/couche5_01.h"

/* fonctions */

int main(void)
/// \brief Main
/// \return EXIT_SUCCESS le programme n'a pas eut d'encombre sinon il aurrai rencontré un exit(EXIT_FAILURE)
{
  r0_init_disk_raid5("disk/raid5");

  interpret();

  eteindre_disk_raid5();

  return EXIT_SUCCESS;
}
