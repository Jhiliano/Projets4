/// \file main.c
/// \brief ficher main
/// \author Guillaume Fourcroy
/// \date 24 février 2019

/* dépendances */

#include "../headers/Raid5/couche5.h"

/* fonctions */

int main(void)
/// \brief Main
/// \return EXIT_SUCCESS le programme n'a pas eut d'encombre sinon il aurrai rencontré un exit(EXIT_FAILURE)
{
  init_disk_raid5("disk");
  store_file_to_host("tests/in/image1.png");
  store_file_to_host("tests/in/image2.png");
  store_file_to_host("tests/in/text1.txt");
  store_file_to_host("tests/in/text2.txt");
  store_file_to_host("tests/in/text3.txt");
  store_file_to_host("tests/in/text4.txt");
  store_file_to_host("tests/in/compress.zip");
  eteindre_disk_raid5();

  return EXIT_SUCCESS;
}
