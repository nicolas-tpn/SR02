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
	int temp_index = arg.lower_bound; 

	while (temp_index <= arg.upper_bound) {
		// on met à faux les valeurs du tableau concernées 
		array[temp_index] = 0;     
		temp_index += arg.index;
	}

	pthread_mutex_lock(&mutex);
    activeThreads--;
    pthread_cond_signal(&condition);
    pthread_mutex_unlock(&mutex);
    
    return NULL;
}

void creat_thread(int k, int nb_max) {

	pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);

    activeThreads = k;

		
	if (k > nb_max) {
		//on créé nb_max threads
		for (int i = 0; i<nb_max; i++) {
			if ((pthread_create(&(thread_array[i].thread), NULL, void *thread_execution, data_thread *arg))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}
		}
	

	} else {
		//on créé k threads
		for (int i = 0; i<k; i++) {
			if ((pthread_create(&(thread_array[i].thread), NULL, void *thread_execution, data_thread *arg))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}
		}

		
	}

	pthread_mutex_lock(&mutex);

    while (activeThreads > 0) {
        pthread_cond_wait(&condition, &mutex);
    }
    pthread_mutex_unlock(&mutex);
    
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&condition);

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
			
			int elements = ceil((n-(i*i))/i) //nombre d'élements qu'on va devoir traiter

			//Répartition des élements entre k threads :
			if (k > elements){
				// Un thread par élément
			}
			else {
				// On répartie les éléments pour les threads
			}

			;

		}
		
	}

	return 0;

}
