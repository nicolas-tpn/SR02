#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "sharmem.h"

int main(int argc, char* argv[]) {

	int fd;
	long taille_fichier;
	char* contenu;
	struct stat etat_fichier;
	char tmp;

	// Vérifier qu'on a bien reçu un nom de fichier
	if (argc < 2) {
		fprintf(stderr,"Erreur d'usage : %s <file> \n",argv[0]);
		exit(EXIT_FAILURE);
	}

	fd = open(argv[1], O_RDWR, 0666);

	//Vérifier que le fichier s'est ouvert correctement
	if (fd == -1) {
		perror("Erreur ouverture fichier");
		exit(EXIT_FAILURE);
	}

	//Vérifier que les informations sur le fichier ont bien été récupérées
	if (stat(argv[1], &etat_fichier) == -1){
		perror("stat");
		exit(EXIT_FAILURE);
	}

	taille_fichier = etat_fichier.st_size;

	contenu = (char*)mmap(NULL, taille_fichier, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	
	//Vérifier que le fichier a bien été mappé en mémoire
	if (contenu == (char*) MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	//Vérifier que le fichier s'est fermé correctement
	if (close(fd)== 1){
		perror("Erreur fermeture fichier");
		exit(EXIT_FAILURE);
	}

	//Inverser le contenu du fichier
	for (int i = 0; i < taille_fichier/2; i++) {
		tmp = contenu[i];
		contenu[i] = contenu[taille_fichier-i-1];
		contenu[taille_fichier-i-1] = tmp;
	}

	//Vérifier que le fichier a bien été unmappé
	if (munmap((void*) contenu, taille_fichier) == -1) {
		perror("munmap");
		exit(EXIT_FAILURE);
	}


	return 0;
}