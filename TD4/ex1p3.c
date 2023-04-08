// On va écrire un programme qui utilise la commincation inter-processus c'est t-a-dire le segment de mémoire partagé entre le parent et le fils pour surveiller et afficher le contenude deux fichiers
#include "sharemem.h"
#define BLKSIZE 1024
#define PERM (S_IRUSR | S_IWUSR) // la macro PERM définie dans l'instruction donnée représents les permissions de fichier qui accordent un accès en lecture et en écriture un propriétaire d'un fichier dans un programme // il s'agit d'une spécification // il n'est pas important de le connaître en détail
#define SHMZ 27 // définir un valeur constante qui représents la taille du bloc de mémoire à
créer
// On doit déclarer à nouveau la fonction copierfichier
int copierfichier(int f1, int f2) // copier le contenu du fichier f1 à f2, la fonction renvoie un entier (la nombre d'octets copiés)
// On va définir les varibales
{
    char buf[BLKSIZE];
    int octetslus;
    int octetsecri;
    int totaloct = 0;
    for( ; ; ) // boucle infini jusq'à la fin du fichier
    {
        if ((octetslus = read(f1, buf, BLKSIZE)) <= 0) // copier le cotenu du f1 dans la tableau de caractères buf
            break;
        if ((octetsecri=write(f2, buf, octetslus)) == -1)// écrire le contenu du tableau buf dans f2
            break;
        totaloct += octetsecri; // Ajouter le nombre d'octets lus à chaque tour au précédent
    }
    return totaloct;
}


// On va maintenant décalrer une autre fonction appelée detachandremove qui sera utilisée pour supprimer le segment de mémoire partagée créé à la fin du programme en utilisant la fonction shmctl
int detachandremove(int shmid, void *shmaddr)
{
    int error=0;
    if(shmdt(shmaddr)==-1)
        error=errno;
    if((shmctl(shmid, IPC_RMID, NULL)==-1 && !error))
        error=errno;
    if(!error)
        return 0;
    errno=error;
        return -1;
}
// On va effectuer les mêmes contrôles d'erruer que dans le programme précédent
int main(int argc, char *argv[]) // la programme prend en entrés la nombre d'arguments fournis au programme, des chaînes de tableau contenant le nom du programme et deux fichiers
// Les paramètres de ce programme sont la mêmes que ceux du programme précédent, à l'exception de l'ajout des int id, int *sharedtotal
{
    int octetslus;
    int childpid;
    int fd, fd1, fd2, id;
    int *sharedtotal;
    int totalbytes=0;
    if(argc!=3)
    {
        fprintf(stderr, "Usage: %s file 1 file 2 \n", argv[0]);
        return 1;
    }
    if ((fd1=open(argv[1], O_RDONLY))==-1 || (fd2=open(argv[2], O_RDONLY))==-1) // ouvrir le fichier 1, s'il ne s'ouvre pas, afficher un message d'erreur
    {
        perror("Echec de l'ouverture du fichier");
        return 1;
    }
    // New part
    if((id=shmget(IPC_PRIVATE, SHMZ, PERM))==-1) // On va maintenant créer le segment demémoire partagée sans clé à l'aide de la fonction shmget(), elle renvoie l'identifiant du segment et vérifie s'il y a une erreur.
    {
        perror("Echec de creation d'un segment");
        return 1;
    }
    // On attache maintenant un pointeur au segment de mémoire partagée à l'aide de lafonction d'appel système shmat() et vérifions s'il y a une erreur
    if ((sharedtotal= (int*)shmat(id, NULL, 0)) == (void*)-1)
    {
        perror("Echec de l'attachment au segment");
    }
    // Créer un processus fils à l'aide de la fonction fork(), s'il n'a pas été créé, afficher un message d'erreur
    if((childpid=fork())==-1)
    {
        perror("Echec de fork");
        if (detachandremove(id, sharedtotal)==-1) // En cas d'erreur lors de la création du processus fils, détachez et supprimez le segment de mémoire créé.
            perror("Echec de detruire le segment");
    }
    if (childpid>0) /*Parent code*/ //si le childpid est positif, cela signifie que nous exécutons le processus parent, du coup, assigner le descripteur de fichier fd1 à fd.
        fd = fd1;
    else
        fd = fd2;
    while ((octetslus=copierfichier(fd, STDOUT_FILENO)) > 0) // Utilisez la fonction copierfichier pour copier le contenu de fd par parent et fils vers le descripteur de fichier de sortie standard à afficher, puis renvoyer le nombre d'octets lus
        totalbytes += octetslus;
    if (childpid == 0) /*child code*/ // Dans le processus fils, écrire les octets lus dans le segment de mémoire partagée
    {
        *sharedtotal=totalbytes;
        return 0;
    }
    // maintenant, le parent doit attendre que le processus fils termine son processus en utilisant la fonction wait()
// Puis afficher le nombre d'octets lus par le parent, le fils et le nombre total d'octets
    if (wait(NULL) == -1) //
        perror("Echec de wait");
    else
    {
        fprintf(stderr, "Octets copiés: %8d par le parent\n", totalbytes);
        fprintf(stderr, "%8d Octets copiés par le fils\n", *sharedtotal);
        fprintf(stderr, "Octet total copiés: %8d\n", totalbytes+ *sharedtotal);
    }
//
    if(detachandremove(id, sharedtotal) == -1) // SUpprimer le segment de mémoire créé
        perror("Echec de detruire le segment");
    return 0;
}
