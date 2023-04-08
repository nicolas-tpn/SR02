// On va écrire un programme qui utilise les processus parent et fils pour surveiller et afficher le contenu de deux fichiers
#include "sharemem.h"
#define BLKSIZE 1024 // Définir une valeur constante qui peut être utilisée dans le programme

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

int main(int argc, char *argv[]) // la programme prend en entrés la nombre d'arguments fournis au programme, des chaînes de tableau contenant le nom du programme et tableau des argument de ligne de commande qui contient le chemin d'accès au fichier
// On va définir les variables
{
    int octetslus;
    int childpid;
    int fd, fd1, fd2;
    if (argc != 3) // vérifie si les arguments sont au nombre 3, sinon affiche un message d'erreur
    {
        fprintf(stderr, "Usage: %s fichier 1 fichier 2 \n", argv[0]);
        return 1;
    }
    if ((fd1 = open(argv[1], O_RDONLY)) == -1) // ouvrir le fichier 1, s'il ne s'ouvre pas, afficher un message d'erreur
    {
        fprintf(stderr, "Echec de l'ouverture du fichier %s:%s\n", argv[1], strerror(errno));
        return 1;
    }
    if ((fd2 = open(argv[2], O_RDONLY)) == -1)// La même chose pour le fichier f2
    {
        fprintf(stderr, "Echec de l'ouverture du fichier %s:%s\n", argv[2], strerror(errno));
        return 1;
    }
    if ((childpid = fork()) == -1) // Créer un processus fils à l'aide de la fonction fork(), s'il n'a pas été créé, afficher un message d'erreur
    {
        perror("parent echec de fork()");
        return 1;
    }
    if (childpid > 0) /*Parent code*/ // si le childpid est positif, cela signifie que nous exécutons le processus parent, du coup, assigner le descripteur de fichier fd1 à fd.
        fd=fd1;
    else // autre
        fd=fd2;
    octetslus=copierfichier(fd, STDOUT_FILENO); // Utilisez la fonction copierfichier pour copier le contenu de fd par parent et fils vers le descripteur de fichier de sortie standard à afficher, puis renvoyer le nombre d'octets lus.
    fprintf(stderr, "Octets lus: %d\n", octetslus); // Afficher les octets lus par les processus parent et fils.
// Notez que lorsque nous exécutons le prog, celui-ci affiche le nombre de contenus +1, et ceci est dû au caractère '\0' qui est compté automatiquement à la fin de chaque fichier
    return 0;
}
