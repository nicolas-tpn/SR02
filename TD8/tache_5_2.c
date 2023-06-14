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
int compteur = 1;
int k, n;
pthread_t *thread_array;
int *array;


void *thread_execution(void *num) {
	int lower_bound;
	int upper_bound;
	int value = *(int *)num;

	/* boucle avec un pas de 2i */
	for (int j = 2; j < sqrt(n); j++) {

		//Calcul des tranches (slices)
		int nb_elem = ceil((n-(j*j))/j);
		
		lower_bound = ceil(j * j + (nb_elem * value / k) * j);
		upper_bound = ceil(j * j + (nb_elem * (value + 1) / k) * j);
		

		for (int h = lower_bound; h <= upper_bound; h += j) {
			if (h%2 != 0){
				int e;
				e = (h/2) - 1;

				array[e] = 0;
			
			}
			
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

    array = malloc(((n+1)/2) * sizeof(int));
    thread_array = malloc(k * sizeof(pthread_t));
	
	start = clock();

	// Initialisation du tableau booléen (1 pour vrai, 0 pour faux)
	array[0] = 1; // 2
	array[1] = 1; // 3
	array[2] = 1; // 5
	// Les autres éléments du tableau sont initialisés à 1 par défaut
	for (int i = 3; i < (n+1)/2; i++) {
		array[i] = 1;
	}
	
	// Création des threads
	creat_thread(k);

	for (int w = 0; w < k; w++) {
		pthread_join(thread_array[w], NULL);
	}

	printf("Les nombres premiers avant %d sont : \n", n);
	printf("2\n");
	for (int l = 0; l < ((n+1)/2)-1; l++) {
		if (array[l] == 1) {
			// Vérification des valeurs des nombres premiers
			printf("%d\n", 2*l+3);
			compteur++;
		}
	}
	
	// Vérification du nombre de nombres premiers
	printf("\nIl y a %d nombres premiers\n", compteur);

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("%f\n", cpu_time_used);
	return 0;
}