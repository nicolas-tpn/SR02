#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

#define MAX 10000000
#define K 7

void creat_thread(int k, int nb_max);
void *thread_execution(void *num);
int max(int nb_1, int nb_2);

clock_t start, end;
double cpu_time_used;

int k, n;
pthread_t thread_array[K];

int array[MAX];

int min(int nb_1, int nb_2) {
    return (nb_1 < nb_2) ? nb_1 : nb_2;
}

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
		upper_bound = min(upper_bound, n);
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
			if ((pthread_create(&(thread_array[i]), NULL, thread_execution, numero))) {
				fprintf(stderr, "pthread_create error \n");
				exit(EXIT_FAILURE);
			}

		}
		
	}

}

int main (int argc, char* argv[]) {

	if (argc < 3) {
        printf("Veuillez fournir deux valeurs en argument.\n");
        return 1;
    }

    k = atoi(argv[1]);
    n = atoi(argv[2]);
	
	/*
	printf("Nombre de thread implques? (entre 1 et 7) :");
	scanf("%d", &k);
	if (k>7||k<1) {
		fprintf(stderr, "Mauvais nombre de thread \n");
	}
	printf("Veuillez entrer la taille du crible : \n");
	scanf("%d", &n);
	*/
	start = clock();

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

	//printf("Les nombres premiers nombres presents avant %d sont : \n", n);
	for (int l = 2; l<n; l++) {
		if (array[l] == 1) {
			printf("%d\n", l);
		}
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	//printf("%f \n", cpu_time_used);

	return cpu_time_used;

}
