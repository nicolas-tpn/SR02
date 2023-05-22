#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#define N_SEM 5

union semun {
	int val;
	struct semid_ds *buf;
	ushort *array;
};


static struct sembuf op_P = {-1, -1, 0};
static struct sembuf op_V = {-1, 1, 0};

static int semid = -1; 
int init_semaphore(void);
int detruire_semaphore(void);
int val_sem(int sem, int val);
int P(int sem);
int V(int sem);
