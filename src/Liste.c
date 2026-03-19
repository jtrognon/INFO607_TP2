#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Liste.h"


Liste * creerListe()
{
    return NULL;
}


bool vide(Liste * liste)
{
    return liste == NULL;
}


void prefixer(Liste ** liste, Element element)
{
    /**
     * \brief Ajoute un element en tete de liste.
     * \param liste Adresse de la liste a modifier.
     * \param element Element a ajouter.
     */
    Liste * tete = (Liste *) malloc(sizeof(Liste));

    tete->valeur = element;
    tete->suivant  = *liste;
    *liste = tete;
}


void suffixer(Liste ** liste, Element element)
{
    /**
     * \brief Ajoute un element en fin de liste 
     * \param liste Adresse de la liste a modifier.
     * \param element Element à ajouter.
     */
    if (vide(*liste))
    {
        prefixer(liste, element);
    }
    else
    {
        Liste * ptInt = *liste;

        while (!vide(reste(ptInt)))
        {
            ptInt = reste(ptInt);
        }

        Liste * tail = (Liste *) malloc(sizeof(Liste));
        tail->valeur = element;
        tail->suivant = NULL;

        ptInt->suivant = tail;
    }
}


Element premier(Liste * liste)
{
    if (vide(liste))
    {
        fprintf(stderr, "premier: La liste donnée est vide.\n");
    }
    
    return liste->valeur;
}


Liste * reste(Liste * liste)
{
    if (vide(liste))
    {
        fprintf(stderr, "reste: La liste donnée est vide.\n");
    }
    
    return liste->suivant;
}


void afficherListe(Liste * liste)
{
    /**
     * \brief Affichage de la liste d'elements.
     * \param liste Liste des elements a afficher. 
     */
    if (!vide(liste))
    {
        Liste * eCourant = liste;
        
        while (!vide(reste(eCourant)))
        {
            printf("%c -> ", premier(eCourant));

            eCourant = reste(eCourant);
        }

        printf("%c", premier(eCourant));
    }
}

void libererListe(Liste * liste)
{
    /**
     * \brief Libere la memoire de la liste.
     * \param liste Liste a vider
     */
    if (!vide(liste))
    {
        
        libererListe(reste(liste));
        free(liste);
    }
}




void testListe()
{
    // ================= Liste vide =================
    Liste * listeVide = creerListe();
    Test(listeVide == NULL, "Création d'une liste vide.");
    
    // ================= Prefixer =================
    // Liste vide
    Liste * l1 = creerListe();
    Element v1 = 'b';
    prefixer(&l1, v1);
    Test(l1->valeur == v1 && l1->suivant == NULL, "Préfixer sur une liste vide.");

    // Liste non vide
    Element v2 = 'a';
    prefixer(&l1, v2);
    Test(l1->valeur == v2 && l1->suivant->valeur == v1 && l1->suivant->suivant == NULL, "Préfixer sur une liste non vide.");


    // ================= Suffixer =================
    // Liste vide
    Liste * l2 = creerListe();
    suffixer(&l2, v2);
    Test(l2->valeur == v2 && l2->suivant == NULL, "Suffixer sur une liste vide.");

    // Liste non vide
    suffixer(&l2, v1);
    Test(l2->valeur == v2 && l2->suivant->valeur == v1 && l2->suivant->suivant == NULL, "Suffixer sur une liste non vide.");


    // ================= Fonction 'vide' =================
    // Liste vide
    Test(vide(listeVide), "'vide' sur une liste vide.");

    // Liste non vide
    Test(!vide(l1), "'vide' sur une liste non vide.");


    // ================= Premier =================
    // Liste vide
    // premier(listeVide); // Provoque une erreur.

    // Liste non vide
    Test(premier(l1) == v2, "Premier élément d'une liste non vide.");

    // ================= Reste =================
    // Liste vide
    // reste(listeVide); // Provoque une erreur.

    // Liste non vide
    Liste * resteL1 = reste(l1);
    Test(resteL1->valeur == v1 && vide(reste(resteL1)), "Reste d'une liste non vide.");



    // Test de libération de la mémoire avec 'valgrind --leak-check=full ./<executable>'
    libererListe(l1);
    libererListe(l2);
}