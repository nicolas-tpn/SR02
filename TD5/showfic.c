#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include "sharmem.h"

int main (int argc, char* argv[]) {

	int i,fd;
	fd=open("titi.dat",O_RDWR,0666);
	int taille_fichier;

	//taille_fichier = fichier.st_size;
	taille_fichier = 10*sizeof(int);

	int* tab1 = (int*) mmap(NULL, taille_fichier, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    
	if (tab1 == (int*)MAP_FAILED) {
		perror("mmap");
		exit(0);
	}

	close(fd);
    
	while (1) {
        scanf("%d", &i);

        if (i == 99) {
            return 0;
        }

        for (int j = 0; j < 10; j++) {
        	fprintf(stdout, " %d ", tab1[j]);
        }

        fprintf(stdout, "\n");
    }

    munmap((void*) tab1, 10*sizeof(int));

    return 0;

}
