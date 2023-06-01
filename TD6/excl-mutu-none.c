#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
	
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
			A = *shm;
			usleep((rand()% (101-20)));
			A++;
			*shm = A;
			usleep((rand()% (101-20)));
			printf("%d\n", A);
		}
	} else {
		// dans le processus père
		for (int i=0; i<100; i++) {
			// section critique
			A = *shm;
			usleep((rand()% (101-20)));
			A++;
			*shm = A;
			usleep((rand()% (101-20)));
			printf("%d", E);
		}
	}

	return 0;
}