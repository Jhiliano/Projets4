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
  eteindre_disk_raid5();

  return EXIT_SUCCESS;
}
