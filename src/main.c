// #define DEBUG

#include <time.h>
#include "Liste.h"

void comparaisonTempsListe();

int main()
{
    srand(time(NULL));

    #ifdef DEBUG
        testPile();
        testListe();
    #endif

    comparaisonTempsListe();
    
    return 0;
}


Liste * _listeAleatoire(int N, int maxInt)
{
    Liste * l = creerListe();
    
    for (int i = 0; i < N; i++)
    {
        l = suffixer(l, rand() * maxInt);
    }
    
    return l;
}


void comparaisonTempsListe()
{
    for (int i = 1; i < 2<<12; i+=i)
    {
        // ======== Grande plage de valeurs possibles ========
        Liste * grandePlage = _listeAleatoire(i, i);        

        // Iteratif
        clock_t debutIt = clock();
        tri_it(grandePlage);
        clock_t finIt = clock();
        // printf("Temps de traitement du tri fusion iteratif sur une grande plage de valeurs : %f.\n", (float)(finIt - debutIt) / CLOCKS_PER_SEC);
        printf("%d\t%.9f\n", i, (float)(finIt - debutIt) / CLOCKS_PER_SEC);
        
        // Recursif
        clock_t debutRec = clock();
        tri_rec(grandePlage);
        clock_t finRec = clock();
        // printf("Temps de traitement du tri fusion recursif sur une grande plage de valeurs : %f.\n", (float)(finRec - debutRec) / CLOCKS_PER_SEC);
        // printf("%d\t%.9f\n", i, (float)(finRec - debutRec) / CLOCKS_PER_SEC);


        // ======== Petites plage de valeurs possibles ========
        Liste * petitePlage = _listeAleatoire(i, 10);    

        // Iteratif
        debutIt = clock();
        tri_it(petitePlage);
        finIt = clock();
        // printf("Temps de traitement du tri fusion iteratif sur une petite plage de valeurs : %f.\n", (float)(finIt - debutIt) / CLOCKS_PER_SEC);
        // printf("%d\t%.9f\n", i, (float)(finIt - debutIt) / CLOCKS_PER_SEC);

        // Recursif
        debutRec = clock();
        tri_rec(petitePlage);
        finRec = clock();
        // printf("Temps de traitement du tri fusion récursif sur une petite plage de valeurs : %f.\n", (float)(finRec - debutRec) / CLOCKS_PER_SEC);
        // printf("%d\t%.9f\n", i, (float)(finRec - debutRec) / CLOCKS_PER_SEC);
    }
    
}
