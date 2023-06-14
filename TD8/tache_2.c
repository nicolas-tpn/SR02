#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main (int argc, char* argv []) {

	/* Tache 2 */

	/* Implémentation du crible en version séquentielle */
	int input;
	clock_t start,end;
	double cpu_time_used;
	int compteur = 0;

	// Vérification de la présence de l'argument n en ligne de commande
	if (argc < 2) {
		printf("Veuillez fournir un entier n en argument.\n");
		return 1;
	}

	// Récupération de la valeur de n
	input = atoi(argv[1]);

	start = clock();

	// Allocation dynamique du tableau pour stocker les booléens
	int *array = malloc(input*sizeof(int));
	
	// Initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	for (int i = 2; i < input; i++) {
		array[i] = 1;
	}

	// Algorithme du crible d'Ératosthène
	for (int j = 2; j < sqrt(input); j++) {
		if (array[j] == 1) {
			int m = j * j;
			while (m < input) {
				array[m] = 0;
				m += j;
			}
		}
	}

	end = clock();

	// Comptage et affichage des nombres premiers
	for (int k = 2; k < input; k++) {
		if (array[k] == 1) {
			//printf("%d\n", k);
			compteur++;
		}
	}

	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	/* Fin Tache 2 */
	printf("%f \n", cpu_time_used);
	//printf("\n%d\n", compteur);

	return 0;
}