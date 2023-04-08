// Les principaux objectifs de ce programme sont d'assurer la communincation inter-processus un segment de mémoire commun à l'aide d'une clé prédéfinie entre le serveur et le client.
#include "sharemem.h"
#define SHMSZ 27
// nous définissons tous les paramètres
int main()
{
    char c;
    int shmid;
    key_t key;
    char *shm,*s;
    key = 2017;
    // Créer le segment avec le clé key=2017
    if ((shmid=shmget(key, SHMSZ, IPC_CREAT|0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }
    printf("Création d'un segment de mémoire avec shmid=%d\n", shmid); // afficher que le segment de mémoire partagée est créé et de l'ID correspodant
    // Attacher le seg.
    if ((shm=shmat(shmid, NULL, 0)) == (char*)-1) // vérifier les erreurs
    {
        perror("shmat");
        _exit(1);
    }
    // Effacer le contenu d'une région de mémoire partagée en utilisant memset, juste pour s'assurer que la mémoire est vide
    memset(shm, 0, SHMSZ);
    // Mettre quelques choses dans la mémoire pour l'autre processus
    s=shm;
    for(c='a'; c<'z'; c++)
    {
        *s++=c; // Assigner une valeur à l'emplacement mémoire pointé par la variable "s" et ensuite incrémenter le pointeur pour sur l'emplacement mémoire suivant.
    }
    *s='\0'; // Assigner le dernier caractère par NULL
    // Enfin, attendant que l'autre processus modifie le premier caractère de notre mémoire en '*', indiquant qu'il a lu ce que nous avons mis
    while (*shm!='*')
        sleep(1);
    // Une fois que le client a terminé son processus, nous devons détacher et supprimer la mémoire partagée
    // détacher le pointeur de la mémoire partagée
    if (shmdt(shm) == -1)
    {
        perror("shmdt");
        _exit(1);
    }
    // une fois que le fils a terminé son processus, afficher que le processus est terminé
    printf("Le client met fin au processus\n");
    printf("Le processus est terminé et le segment de mémoire créé est supprimé \n");
    // Supprimer le segment de mémoire créé en utilisant la fonction shmctl
    if(shmctl(shmid, IPC_RMID, NULL) == -1) // vérifier les erreurs
    {
        perror("shmctl");
        _exit(1);
    }
    _exit(0); // mettre fin à lexécution du programme
    return 0;
}
