#include "sem_pv.h"

int main(int argc, char const *argv[]) {
	
	pid_t pid;
	int shmid;

	if ((shmid = shmget(IPC_PRIVATE, 5*sizeof(int), IPC_CREAT | 0666)) == -1) {
		fprintf(stderr, "shmget");
		return -1;
	}

	int *shm;
	if ((shm = shmat(shmid, NULL, 0)) < (int*) 0) {
		fprintf(stderr, "shmat");
		return -1;	
	}

	init_semaphore();
	val_sem(0, 5); // sémaphore de vide
	val_sem(1, 0); // sémaphore de plein

	if (pid = fork() == -1) {
		fprintf(stderr, "fork");
		return -1;
	}

	if (pid == 0) {
		// dans le processus fils
		int index_fils = 0;
		for (int i=0; i<50;i++) {
			P(0);
			shm[index_fils % 5] = i+1;
			printf("Ecrire : %d\n",shm[index_fils % 5]);
			index_fils++;
			usleep(1000*100*(rand()%6));
			V(1);
		}
		exit(0);
		
	} else {
		// dans le processus père
		int index_pere = 0;
		for (int j=0; j<50; j++) {
			P(1);
			printf("Lit : %d\n",shm[index_pere % 5]);
			index_pere++;
			usleep(1000*100*(rand()%6));
			V(0);
		}
		wait(NULL);
	}

	if(shmctl(shmid,IPC_RMID,NULL)==-1){
		perror("Error - shmctl");
		exit(1);
	}

	detruire_semaphore();

	return 0;
}