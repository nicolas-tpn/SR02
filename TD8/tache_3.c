#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define MAX 10000

void creat_thread(int k, int nb_max);
void *thread_execution(void *num);

int k, n;
pthread_t thread_array[MAX];

int array[MAX];

void* thread_execution(void *num) {
	int lower_bound;
	int upper_bound;
	int* value = (int*)num;
	
	for (int j = 2; j<=floor(sqrt(n)); j++) {
		//Calcul slices 
		int nb_elem = ceil((n-(j*j))/j);
		int chunk = ceil(n-(j*j)/k);
		
		lower_bound = j*j + (*value)*chunk;
		upper_bound = j*j + (*value+1)*chunk;
		// Ligne pour debug/verification des valeurs des bornes
		//printf("Thread numero %d : [%d; %d] \n",*value, lower_bound, upper_bound);
		
		for (int h = lower_bound; h<upper_bound; h+=j) {
			array[h] = 0;	
		}
	}

	pthread_exit(NULL);

}

void creat_thread(int k, int nb_max) {
	
	if (k > nb_max) {
		//on créé nb_max threads
		for (int i = 0; i<nb_max; i++) {
			int numero = i;
			
			if ((pthread_create(&(thread_array[i]), NULL, thread_execution, &numero))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}
		}

	} else {
		//on créé k threads
		for (int i = 0; i<k; i++) {
			int* numero = malloc(sizeof(int));
			*numero = i;
			printf("%d\n", i);
			if ((pthread_create(&(thread_array[i]), NULL, thread_execution, numero))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}

		}
		
	}

}

int main (int argc, char* argv[]) {

	/*
	if (argc != 2){
		fprintf(stderr, "Erreur, pas assez de paramètres\n");
		return -1;
	}
	*/
	
	//n = atoi(argv[1]);
	k = 7;
	printf("Veuillez entrer la taille du crible : \n");
	scanf("%d", &n);

	// Initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	for (int i = 2; i<n; i++) {
		array[i] = 1;
	}
	// Création des threads
	double nb_elements_max = ceil((n-4)/2);
	creat_thread(k, nb_elements_max);

	for (int w = 0; w<k; w++) {
		pthread_join(thread_array[w], NULL);
	}

	printf("Les nombres premiers nombres presents avant %d sont : \n", n);
	for (int l = 2; l<n; l++) {
		if (array[l] == 1) {
			printf("%d\n", l);
		}
	}

	return 0;

}
