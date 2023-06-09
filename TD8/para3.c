#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX 10000

struct data_thread {
	pthread_t thread;
	int numero;
	int lower_bound;
	int upper_bound;
	int index;  
};
typedef struct data_thread data_thread;

void creat_thread(int k, int nb_max);
void *thread_execution(void *num);

int k, n;
//data_thread thread_array[MAX];
pthread_t thread_array[MAX];

int array[MAX];
pthread_mutex_t mutex;
pthread_cond_t condition;
int activeThreads; // Nombre de threads actifs

void* thread_execution(void *num) {
	int lower_bound;
	int upper_bound;
	int* value = (int*)num;
	
	for (int i = 2; i<=sqrt(n); i++) {
		//Calcul slices 
		int elements = ceil((n-(i*i))/i);
		//printf("\n elements %d\n",elements);
		lower_bound = i*i + (*value)*elements/k;
		upper_bound = i*i + (*value+1)*elements/k;
		printf("Thread numero %d : [%d; %d] \n",*value, lower_bound, upper_bound);
	}
	
	return NULL;
	
}

void creat_thread(int k, int nb_max) {

	pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&condition, NULL);

    activeThreads = k;
	
	if (k > nb_max) {
		//on créé nb_max threads
		for (int i = 0; i<nb_max; i++) {
			int numero = i;
			printf("\n creation de thread opt 1\n");
			
			if ((pthread_create(&(thread_array[i]), NULL, thread_execution, &numero))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}
		}

	} else {
		//on créé k threads
		for (int i = 0; i<k; i++) {
			int numero = i;
			//printf("\n Creation de thread opt 2\n");
			printf("%d\n", i);
			if ((pthread_create(&(thread_array[i]), NULL, thread_execution, &numero))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}

		}
		
	}

}

int main (int argc, char* argv[]) {

	if (argc != 3){
		fprintf(stderr, "Erreur, pas assez de paramètres\n");
		return -1;
	}
	
	n = atoi(argv[1]);
	k = atoi(argv[2]);

	// Initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	for (int i = 2; i<n; i++) {
		array[i] = 1;
	}
	// Création des threads
	double nb_elements_max = ceil((n-4)/2);
	creat_thread(k, nb_elements_max);


	return 0;

}
