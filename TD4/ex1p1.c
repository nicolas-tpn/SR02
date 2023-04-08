#include "sharemem.h"
#define BLKSIZE 1024 // Définir une valeur constante BLKSIZE=1024 qui peut être utilisée dans le programme
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
