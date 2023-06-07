#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX 10000

typedef struct data_thread data_thread;
struct data_thread {
	int lower_bound;
	int upper_bound;
};

void creat_thread(int k, int nb_max);
void array_engine(data_thread arg);

int k, n;
p_thread thread_array[MAX];
int array[MAX];

void array_engine(data_thread arg) {

}

void creat_thread(int k, int nb_max) {
		
		if (k > nb_max) {
			//on créé nb_max threads
			for (int i = 0; i<nb_max; i++) {
				if ((pthread_create(&thread_array[i], NULL, void *array_engine, data_thread *arg))) {
					fprintf(stderr, "pthread_create error");
					exit(EXIT_FAILURE);
				}
			}

			break;

		} else {
			//on créé k threads
			for (int i = 0; i<k; i++) {
				if ((pthread_create(&thread_array[i], NULL, void *array_engine, data_thread *arg))) {
					fprintf(stderr, "pthread_create error");
					exit(EXIT_FAILURE);
				}
			}

			break;
		}
}

int main (int argc, char* argv []) {

	if (argc != 3){
		fprintf(stderr, "Erreur, pas assez de paramètres\n");
		return -1;
	}

	n = argv[1];
	k = argv[2];
	
	// Initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	for (int i = 2; i<n; i++) {
		array[i] = 1;
	}

	// Création des threads
	double nb_elements_max = ceil((n-4)/2);
	creat_thread(k, nb_elements_max);

	//Boucle externe
	for (i=2; i<sqrt(n); i++) {
		if (array[i] == 1) {

		}
		
	}

	return 0;

}
