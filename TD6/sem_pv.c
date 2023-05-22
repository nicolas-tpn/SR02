#include "sem_pv.h"


int init_semaphore(void) {

	if (semid != -1) {
		fprintf(stderr, "Init deja appele\n" );
		return -1;
	}

	if (semid = semget(IPC_PRIVATE, N_SEM, 0666) == -1) {
		fprintf(stderr, "Echec de semget");
		return -2; 
	} 
	
	union semun arg;
	arg.val = 0;

	for (int i = 0; i<N_SEM; i++) {
		if (semctl(semid, i, SETVAL, arg) == -1)  {
			fprintf(stderr, "Echec de semctl");
			return -2; 
		} 
	}

	return 0;
}

int detruire_semaphore(void) {
	
	if (semid == -1) {
		fprintf(stderr, "Init jamais appele\n" );
		return -1;
	} 

	int val = semctl(semid, 0, IPC_RMID, 0);
	semid = -1;

	return val;

}

int val_sem(int sem, int val) {

	if (semid == -1) {
		fprintf(stderr, "Init jamais appele");
		return -1;
	}

	if (sem<0 || sem>N_SEM) {
		fprintf(stderr, "Problème numéro de sémaphore");
		return -2;	
	}

	union semun arg;
	arg.val = val;

	int return_value;
	if (return_value = semctl(semid, sem, SETVAL, arg) == -1) {
		fprintf(stderr, "Erreur semctl\n");
		return -2;
	}

	return return_value;
}

int P(int sem) {

	if (semid == -1) {
		fprintf(stderr, "Init jamais appele");
		return -1;
	}

	if (sem<0 || sem>N_SEM) {
		fprintf(stderr, "Problème numéro de sémaphore");
		return -2;	
	}

	op_P.sem_num = sem;

	int return_value;
	if (return_value = semop(semid, &op_P, 1) == -1) {
		fprintf(stderr, "Echec de semop");
		return -2;
	}

	return return_value;
}

int V(int sem) {

	if (semid == -1) {
		fprintf(stderr, "Init jamais appele");
		return -1;
	}

	if (sem<0 || sem>N_SEM) {
		fprintf(stderr, "Problème numéro de sémaphore");
		return -2;	
	}

	op_V.sem_num = sem;

	int return_value; 
	if (return_value = semop(semid, &op_V, 1) == -1) {
		fprintf(stderr, "Echec de semop");
		return -2;
	}

	return return_value;
}

int main () {
	return 0;
}