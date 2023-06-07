#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char* argv []) {

	/* Implémentation du crible en version séquentielle*/
	int input;
	printf("Veuillez entrer la taille du crible : \n");
	scanf("%d", &input);

	if (input<1) {
		fprintf(stderr, "Le nombre entre doit etre superieur a 1\n");
		return -1;
	}

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

	printf("Les %d premiers nombre premiers sont : \n", input);
	for (int k = 2; k<input; k++) {
		if (array[k] == 1) {
			printf("%d\n", k);
		}
	}





	return 0;
}