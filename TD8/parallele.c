#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#define MAX 10000

int k, n;

void create_thread(int k, int nb_max) {
		if (k > nb_max) {
			//on créé nb_max threads


		} else {
			//on créé k threads


		}

}

int main (int argc, char* argv []) {

	if (argc != 3){
		fprintf(stderr, "Erreur, pas assez de paramètres\n");
		return(1);
	}

	n = argv[1];
	k = argv[2];

	int array[MAX];
	
	// Initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	for (int i = 2; i<n; i++) {
		array[i] = 1;
	}

	// Création des threads
	double nb_elements_max = ceil((n-4)/2);



	//Boucle externe
	for (i=2; i<sqrt(n);i++){
		if (array[i] == 1){
			
		}
		
	}

	



}
