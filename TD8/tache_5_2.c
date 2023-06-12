#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

void creat_thread(int k, int nb_max);
void *thread_execution(void *num);

clock_t start, end;
double cpu_time_used;
int compteur = 0;
int k, n;
pthread_t *thread_array;
int *array;

void *thread_execution(void *num) {
	int lower_bound;
	int upper_bound;
	int value = *(int *)num;

	/* boucle avec un pas de 2i */
	for (int j = 2; j < sqrt(n); j++) {

		//Calcul slices 
		int nb_elem = ceil((n-(j*j))/j);
		
		lower_bound = ceil(j * j + (nb_elem * value / k) * j);
		upper_bound = ceil(j * j + (nb_elem * (value + 1) / k) * j);
		
		for (int h = (lower_bound-3)/2; h <= (upper_bound-1)/2; h += 2*j+3) {
			array[h] = 0;	
		}
	}

	pthread_exit(NULL);

}

//2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, et 97.

void creat_thread(int k, int nb_max) {
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

int main (int argc, char* argv[]) {

	if (argc < 3) {
        printf("Veuillez fournir deux valeurs en argument.\n");
        return 1;
    }

    k = atoi(argv[1]);
    n = atoi(argv[2]);

    array = malloc(((n+1)/2)*sizeof(int));
    thread_array = malloc((k)*sizeof(pthread_t));
	
	start = clock();

	// Initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	for (int i = 2; i<(n+1)/2; i++) {
		array[i] = 1;
	}
	// Création des threads
	double nb_elements_max = ceil((n-4)/2);
	creat_thread(k, nb_elements_max);

	for (int w = 0; w < k; w++) {
		pthread_join(thread_array[w], NULL);
	}

	//printf("Les nombres premiers nombres presents avant %d sont : \n", n);
	for (int l = 2; l < (n+1)/2; l++) {
		if (array[l] == 1) {
			// Vérification des valeurs des nombres premiers
			printf("%d\n", 2*l+3);
			compteur++;
		}
	}

	// Verification du nombre de nombres premiers
	//printf("\n Il y a %d nombres premiers", compteur);

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f\n", cpu_time_used);
	return 0;

}
