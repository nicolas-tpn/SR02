#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

int init_semaphore(void);
int detruire_semaphore(void);
int val_sem(int sem, int val);
int P(int sem);
int V(int sem);
