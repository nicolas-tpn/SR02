#include "sem_pv.h"

int main(int argc, char const *argv[]) {
	
	init_semaphore();
	val_sem(1, 1);

	int E = 0;
	int shmid;
	pid_t pid;
	int A;

	if ((shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1) {
		fprintf(stderr, "shmget");
		return -1;
	}

	int* shm;
	if ((shm = shmat(shmid, NULL, 0)) < (int*) 0) {
		fprintf(stderr, "shmat");
		return -1;	
	}

	(*shm) = E;

	if (pid = fork() == -1) {
		fprintf(stderr, "fork");
		return -1;
	}

	if (pid == 0) {
		// dans le processus fils
		for (int i=0; i<100; i++) {
			// section critique
			P(1);
			A = *shm;
			usleep((rand()% (101-20)));
			A++;
			*shm = A;
			usleep((rand()% (101-20)));
			printf("%d\n", A);
			V(1);
		}

	} else {
		// dans le processus père
		for (int i=0; i<100; i++) {
			// section critique
			P(1);
			A = *shm;
			usleep((rand()% (101-20)));
			A++;
			*shm = A;
			usleep((rand()% (101-20)));
			printf("%d", E);
			V(1);
		}
	}

	detruire_semaphore();

	return 0;
}