#ifndef LISTE_H
#define LISTE_H

#include <stdbool.h>

#define MAX_STATS_PAR_ELEMENT 4

#define Test(cond, msg)\
    do{\
        if (cond) {\
            printf("[OK] %s\n", msg);\
        } else {\
            fprintf(stderr, "[FAIL] %s (ligne %d de %s)\n", msg, __LINE__, __FILE_NAME__);\
        }\
    } while(0)

typedef char Element;

typedef struct _Liste
{   
    Element valeur;
    struct _Liste * suivant;
} Liste;



/* ================= Méthodes ================= */

Liste * creerListe();

bool vide(Liste * liste);

Liste * prefixer(Liste * liste, Element element);

Liste * suffixer(Liste * liste, Element element);

Element premier(Liste * liste);

Liste * reste(Liste * liste);

void afficherListe(Liste * liste);

void libererListe(Liste * liste);


Liste * fusion(Liste * l1, Liste * l2);


void testListe();

#endif