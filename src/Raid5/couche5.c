/// \file couche5.c
/// \brief ficher de code couche5
/// \author Guillaume Fourcroy
/// \date 24 février 2019


/* dépendances */


#include "../../headers/Raid5/couche5.h"


/* fonctions */
void interpret(int argc, char*argv[]){
  char *pMots[NBMOTSMAX+1];
	pid_t pidF;
	int i =0;
	printf("> ");
	for(i=0; i<argc; i++){
		printf("%s ", argv[i]);
	}
	printf("\n");

	for(i=1; i<argc; i++){
		pidF=fork();
		switch(pidF){
			case -1:	perror("Echec fork\n");
						exit(1);
			case 0:	printf("[%d] Je lance %s :\n", (int)getpid(), argv[i]);
						Decoupe(argv[i],pMots);
						execvp(pMots[0],pMots);
						perror(argv[i]);
						exit(2);
			default:	printf("[%d] J'ai délégué %s à %d. J'attends sa fin...\n", (int)getpid(), argv[i], (int)pidF);
						wait(NULL);
						printf("[%d] %d terminé.\n", (int)getpid(), (int)pidF);
						printf("[%d] J'ai fini.\n", (int)getpid());
		}
	}
	printf(">\n");
}
