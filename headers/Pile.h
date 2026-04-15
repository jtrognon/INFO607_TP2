#ifndef PILE_H
#define PILE_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define Test(cond, msg)\
    do{\
        if (cond) {\
            printf("[OK] %s\n", msg);\
        } else {\
            fprintf(stderr, "[FAIL] %s (ligne %d de %s)\n", msg, __LINE__, __FILE_NAME__);\
        }\
    } while(0)

typedef struct _Pile{
    void * valeur;
    struct _Pile * suivant;
} Pile;

Pile * creerPile();

bool pile_vide(Pile * pile);

Pile * empiler(Pile * pile, void * liste);

typedef struct {
    Pile * pile;
    void * valeur;
} ResDepiler;
ResDepiler depiler(Pile * pile);


void testPile();

#endif