#include "../../headers/Raid5/couche4.h"


int defrag_raid(void) {
  
}

int main(int argc, char* argv[]) {
  struct stat inforep;
  if (argc != 3) {
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
