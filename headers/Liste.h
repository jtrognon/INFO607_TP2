#ifndef LISTE_H
#define LISTE_H

#include <stdbool.h>

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


Liste * fusion_it(Liste * l1, Liste * l2);
Liste * fusion_rec(Liste * l1, Liste * l2);

Liste * ssc_it(Liste * l);
Liste * ssc_rec(Liste * l);

Liste * comp_it(Liste * l1, Liste * l2);
Liste * comp_rec(Liste * l1, Liste * l2);

Liste * tri_it(Liste * l);
Liste * tri_rec(Liste * l);


void testListe();

void testFusion(Liste * (fusion)(Liste *, Liste *));

void testSsc(Liste * (ssc)(Liste *));

void testComp(Liste * (comp)(Liste *, Liste *));

void testTri(Liste * (tri)(Liste *));
#endif