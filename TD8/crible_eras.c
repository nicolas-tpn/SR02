#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main (int argc, char* argv []) {

	/* Tache 2 */

	/* Implémentation du crible en version séquentielle*/
	int input;
	clock_t start,end;
	double cpu_time_used;
	int compteur = 0;

	if (argc < 2) {
        printf("Veuillez fournir deux valeurs en argument.\n");
        return 1;
    }

    input = atoi(argv[1]);

    /*
	printf("Veuillez entrer la taille du crible : \n");
	scanf("%d", &input);

	if (input<1) {
		fprintf(stderr, "Le nombre entre doit etre superieur a 1\n");
		return -1;
	}
	*/
	start = clock();

	int array[input];
	
	// initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	for (int i = 2; i<input; i++) {
		array[i] = 1;
	}

	for (int j = 0; j<sqrt(input); j++) {
		if (array[j] == 1) {
			int m = j*j;
			while (m<input) {
				array[m] = 0;
				m += j;
			}
		}
	}

	//printf("Les %d premiers nombres premiers sont : \n", input);
	for (int k = 2; k<input; k++) {
		if (array[k] == 1) {
			printf("%d\n", k);
			compteur ++;
		}
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	/* Fin Tache 2 */
	printf("%f \n", cpu_time_used);
	printf("\n%d\n", compteur);


	return 0;
}