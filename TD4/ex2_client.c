// Programme de la client pour communiquer avec le serveur
#include "sharemem.h"
#define SHMSZ 27
int main()
{
    int shmid;
    key_t key;
    char *shm,*s;
    // Obtenir le seg. nommé "2017", créé par le serveur
    key=2017;
    // Localiser le segment
    if((shmid=shmget(key, SHMSZ, 0666))<0)
    {
        perror("The server is not started");
        _exit(1);
    }
    // Attacher le segment à notre espace de données
    if((shm=shmat(shmid, NULL, 0))==(char*)-1)
    {
        perror("shmat");
        _exit(1);
    }
    // Lire ce que le serveur a mis dans la mémoire
    for(s=shm; *s!='\0'; s++)
    {
        putchar(*s);
        putchar('\n');
    }
    // changer le premiur caractère du segment en '*', indiquant que nous avons lu le segment
    *shm='*';
    // Detacher le pointeur du segment
    if((shmdt(shm))==-1)
        perror("shmdt");
    _exit(0);
    return 0;
}
