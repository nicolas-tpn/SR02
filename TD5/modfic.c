#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "sharmem.h"


int main(){

    int i = 0;

	int fd;
	fd=open("titi.dat",O_RDWR,0666);

    if (fd == -1) {
        fprintf(stderr, "Echec de l'ouverture du fichier : %s\n",strerror(errno));
        return 1;
    }

	int* tab1 = (int*) mmap(NULL, 10 * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (tab1 == (int*) MAP_FAILED) {
        perror("mmap");
        exit(0);
    }

    close(fd);

	while (1) {

        scanf("%d", &i);

        if (i == 99) {
            return 0;
        }
        
        tab1[i%10]++; // i%10 car taille de 10
        
    }

    munmap((void*)tab1, 10*sizeof(int));

    return 0;
}