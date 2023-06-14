#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

void creat_thread(int k);
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
	
	/* cas particulier du 2 */
	int nb_elem = ceil((n-(2*2))/2);
	
	lower_bound = ceil(2 * 2 + (nb_elem * value / k) * 2);
	upper_bound = ceil(2 * 2 + (nb_elem * (value + 1) / k) * 2);
	
	for (int h = lower_bound; h <= upper_bound; h += 2) {
		array[h] = 0;	
	}

	/* boucle avec un pas de 2i */
	for (int j = 3; j < sqrt(n); j+=2) {

		//Calcul slices 
		int nb_elem = ceil((n-(j*j))/j);
		
		lower_bound = ceil(j * j + (nb_elem * value / k) * j);
		upper_bound = ceil(j * j + (nb_elem * (value + 1) / k) * j);
		
		for (int h = lower_bound; h <= upper_bound; h += j) {
			array[h] = 0;	
		}
	}

	pthread_exit(NULL);

}

void creat_thread(int k) {
	//on créé k threads
	for (int i = 0; i < k; i++) {
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

    array = malloc((n+1) * sizeof(int));
    thread_array = malloc(k * sizeof(pthread_t));
	
	start = clock();

	// Initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	for (int i = 2; i < n; i++) {
		array[i] = 1;
	}

	// Création des threads
	creat_thread(k);

	for (int w = 0; w < k; w++) {
		pthread_join(thread_array[w], NULL);
	}

	// Affichage des nombres premiers
	for (int l = 2; l < n; l++) {
		if (array[l] == 1) {
			printf("%d\n", l);
			compteur++;
		}
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f\n", cpu_time_used);
	return 0;

}