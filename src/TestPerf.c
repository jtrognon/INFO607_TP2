#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "rabin-karp.c"
#include "brute-force.c"

char *generer_texte(int n)
{
    char *buf = malloc(n + 1);
    for (int i = 0; i < n; i++)
    {
        buf[i] = '0' + (i % 10);
    }
    buf[n] = '\0';
    return buf;
}

int main()
{
    char *motif = "901";
    int tailles[] = {1000, 10000, 100000, 1000000, 10000000};
    int nb_tests = sizeof(tailles) / sizeof(tailles[0]);

    printf("%-15s  %-15s  %-15s\n", "Taille texte", "BruteForce", "RabinKarp");
    printf("%-15s  %-15s  %-15s\n", "------------", "-------------", "------------");

    for (int t = 0; t < nb_tests; t++)
    {
        int n = tailles[t];
        char *texte = generer_texte(n);

        clock_t debut = clock();
        int pos_bf = bruteForce(texte, motif);
        clock_t fin = clock();
        double temps_bf = (double)(fin - debut) / CLOCKS_PER_SEC;

        debut = clock();
        int pos_rk = rabinKarp(texte, motif);
        fin = clock();
        double temps_rk = (double)(fin - debut) / CLOCKS_PER_SEC;

        if (pos_bf != pos_rk)
        {
            printf("ATTENTION : positions différentes ! BF=%d  RK=%d\n", pos_bf, pos_rk);
        }

        printf("%-15d  %-15.6f  %-15.6f\n", n, temps_bf, temps_rk);

        free(texte);
    }

    return 0;
}