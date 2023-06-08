#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX 10000

typedef struct data_thread data_thread;
struct data_thread {
	pthread thread;
	int numero;
	int lower_bound;
	int upper_bound;
	int index;  
};

void creat_thread(int k, int nb_max);
void thread_execution(data_thread arg);

int k, n;
data_thread thread_array[MAX];
int array[MAX];
pthread_mutex_t mutex;
pthread_cond_t condition;
int activeThreads; // Nombre de threads actifs

void* thread_execution(data_thread arg) {
	for (int i = 2; i< sqrt(n); i++) {
		//Calcul slices 
		int elements = ceil((n-(i*i))/i)
		arg.lower_bound = i*i + (arg.numero - 1)*elements/k;
		arg.upper_bound = i*i + (arg.numero)*elements/k;
		printf("Thread numero %d : [%d; %d] \n",numero,arg.lower_bound,arg.upper_bound);
	}
	
}

void creat_thread(int k, int nb_max) {

	pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);

    activeThreads = k;
    int tmp;
		
	if (k > nb_max) {
		//on créé nb_max threads
		for (int i = 0; i<nb_max; i++) {
			thread_array[i].numero = i + 1;

			if ((pthread_create(&(thread_array[i].thread), NULL, void *thread_execution, data_thread *arg))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}
		}

	} else {
		//on créé k threads
		for (int i = 0; i<k; i++) {
			thread_array[i].numero = i + 1;

			if ((pthread_create(&(thread_array[i].thread), NULL, void *thread_execution, data_thread *arg))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}
		}

		
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


	return 0;

}
