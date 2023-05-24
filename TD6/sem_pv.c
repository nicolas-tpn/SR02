#include "sem_pv.h"

#define N_SEM 5

union semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
};


static struct sembuf op_P = {-1, -1, 0};
static struct sembuf op_V = {-1, 1, 0};

static int semid = -1; 

int init_semaphore(void) {
	
	union semun arg;
	arg.val = 0;

	if (semid != -1) {
		fprintf(stderr, "Init deja appele\n" );
		return -1;
	}

	if ((semid = semget(IPC_PRIVATE, N_SEM, 0600)) == -1) {
		fprintf(stderr, "Echec de semget");
		return -2; 
	}

	for (int i = 0; i<N_SEM; i++) {
		semctl(semid, i, SETVAL, arg);
	}

	return 0;
}

int detruire_semaphore(void) {
	
	int val;

	if (semid == -1) {
		fprintf(stderr, "Init jamais appele\n" );
		return -1;
	} 

	val = semctl(semid, 0, IPC_RMID, 0);
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

	return semctl(semid, sem, SETVAL, arg);
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

	return semop(semid, &op_P, 1);
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

	return semop(semid, &op_V, 1);
}