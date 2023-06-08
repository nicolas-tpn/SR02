#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX 10000

typedef struct data_thread data_thread;
struct data_thread {
	pthread thread;
	int lower_bound;
	int upper_bound;
	int index;  // M : c'est bien i ?
};

void creat_thread(int k, int nb_max);
void thread_execution(data_thread arg);

int k, n;
data_thread thread_array[MAX];
int array[MAX];

void thread_execution(data_thread arg) {
	int temp_index = lower_bound; // M :lower_bound c'est pas une variable globale
	//faudrait pas mettre arg.lower_bound plutôt ?

	while (temp_index <= arg.upper_bound) {
		// on met à faux les valeurs du tableau concernées 
		array[temp_index] = 0;     
		temp_index += arg.index;
	}
}

void creat_thread(int k, int nb_max) {
		
		if (k > nb_max) {
			//on créé nb_max threads
			for (int i = 0; i<nb_max; i++) {
				if ((pthread_create(&(thread_array[i].thread), NULL, void *thread_execution, data_thread *arg))) {
					fprintf(stderr, "pthread_create error \n");
					exit(EXIT_FAILURE);
				}
			}

			break;

		} else {
			//on créé k threads
			for (int i = 0; i<k; i++) {
				if ((pthread_create(&(thread_array[i].thread), NULL, void *thread_execution, data_thread *arg))) {
					fprintf(stderr, "pthread_create error \n");
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

	// Boucle externe
	for (i=2; i < sqrt(n); i++) {
		if (array[i] == 1) {
			int thread_array_curser = 0; // vient parcourir le tableau de thread entre 0 et k
			int pow = i*i;
			int seg = n-pow;
			seg = seg/k; 
			// M : j'aurais d'abord fait seg = seg/i pour avoir le nombre d'élem
			//et ensuite seg = seg / k (ou seg = seg / (i*k) )

			int bound = pow;
			int temp_bound = 0;
			while (bound <= n) {
				thread_array[thread_array_curser].lower_bound = bound;
				bound += seg;
				if (bound > n) break;
				/* Il va y avoir un problème ici, pour avoir la borne supérieur 
				on ne va pas forcément tomber sur une des valeurs que l'on veut (càd i²+ki), à solutionner*/
				/* Tentative de solution mais vraiment pas sûr*/
				temp_bound = bound - pow;
				if (temp_bound%i != 0) {
					while (temp_bound%i != 0) {
						temp_bound++;
						bound++;
					}
					temp_bound = 0;
				}
				thread_array[thread_array_curser].upper_bound = bound;
				thread_array[thread_array_curser].index = i;
				thread_array_curser++;
			}

		}
		
	}

	return 0;

}
