#include "sem_pv.h"int main() {			init_semaphore();	val_sem(2, 1);	P(2);	sleep(5);		V(2);	detruire_semaphore();		return 0;}