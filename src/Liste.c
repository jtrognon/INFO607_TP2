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


Liste * prefixer(Liste * liste, Element element)
{
    /**
     * \brief Ajoute un element en tete de liste.
     * \param liste Adresse de la liste a modifier.
     * \param element Element a ajouter.
     * \return La liste avec le nouvel élément.
     */
    Liste * tete = (Liste *) malloc(sizeof(Liste));

    tete->valeur = element;
    tete->suivant  = liste;

    return tete;
}


Liste * suffixer(Liste * liste, Element element)
{
    /**
     * \brief Ajoute un element en fin de liste 
     * \param liste Adresse de la liste a modifier.
     * \param element Element à ajouter.
     * \return La liste avec le nouvel élément.
     */
    if (vide(liste))
    {
        return prefixer(liste, element);
    }
    else
    {
        Liste * ptInt = liste;

        while (!vide(reste(ptInt)))
        {
            ptInt = reste(ptInt);
        }

        Liste * tail = (Liste *) malloc(sizeof(Liste));
        tail->valeur = element;
        tail->suivant = NULL;

        ptInt->suivant = tail;

        return liste;
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


Liste * _copieListe(Liste * l)
{
    /**
     * \brief Renvoie une copie de la liste donnée.
     * \param l La liste à copier.
     * \return Une copie de la liste.
     */
    Liste * res = creerListe();
    Liste * ptInt = l;

    while(!vide(ptInt))
    {
        res = suffixer(res, premier(ptInt));
        ptInt = reste(ptInt);
    }

    return res;
}


Liste * fusion(Liste * l1, Liste * l2)
{
    /**
     * \brief Renvoie une fusion des deux listes.
     * \param l1 La première liste triée à fusionner.
     * \param l2 La deuxième liste triée à fusionner.
     * \return La fusion des deux listes.
     * 
     */
    if (vide(l1))
    {
        return _copieListe(l2);
    }
    
    if (vide(l2))
    {
        return _copieListe(l1);
    }

    if (premier(l1) < premier(l2)) // on insère le premier élément de l1
    {
        return prefixer(fusion(reste(l1), l2), premier(l1));
    }
    else // on insère le premier élément de l2
    {
        return prefixer(fusion(l1, reste(l2)), premier(l2));
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
    l1 = prefixer(l1, v1);
    Test(l1->valeur == v1 && l1->suivant == NULL, "Préfixer sur une liste vide.");

    // Liste non vide
    Element v2 = 'a';
    l1 = prefixer(l1, v2);
    Test(l1->valeur == v2 && l1->suivant->valeur == v1 && l1->suivant->suivant == NULL, "Préfixer sur une liste non vide.");


    // ================= Suffixer =================
    // Liste vide
    Liste * l2 = creerListe();
    l2 = suffixer(l2, v2);
    Test(l2->valeur == v2 && l2->suivant == NULL, "Suffixer sur une liste vide.");

    // Liste non vide
    l2 = suffixer(l2, v1);
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


    // ================= Copie =================
    // Liste vide
    Test(_copieListe(creerListe()) == creerListe(), "Copie d'une liste vide.");

    // Liste non vide
    Liste * l1Bis = _copieListe(l1);
    Test(l1Bis->valeur == v2 && l1Bis->suivant->valeur == v1 && l1Bis->suivant->suivant == NULL, "Copie d'une liste non vide.");


    // ================= Fusion =================
    // Liste A et B vide
    Test(fusion(creerListe(), creerListe()) == creerListe(), "Fusion de deux listes vides.");

    // Liste A vide 
    Liste * B = creerListe();
    B = suffixer(B, 'c');
    B = suffixer(B, 'e');
    B = suffixer(B, 'g');
    B = suffixer(B, 'k');
    B = suffixer(B, 'o');
    B = suffixer(B, 'q');
    Liste * fusion1 = fusion(creerListe(), B);
    Test(premier(fusion1) == 'c' && 
    premier(reste(fusion1)) == 'e' && 
    premier(reste(reste(fusion1))) == 'g' && 
    premier(reste(reste(reste(fusion1)))) == 'k' && 
    premier(reste(reste(reste(reste(fusion1))))) == 'o' &&
    premier(reste(reste(reste(reste(reste(fusion1)))))) == 'q'
    , "Fusion de la liste A (vide) avec la liste B (non vide).");

    // Liste B vide 
    Liste * A = creerListe();
    A = suffixer(A, 'a');
    A = suffixer(A, 'f');
    A = suffixer(A, 'g');
    A = suffixer(A, 'u');
    A = suffixer(A, 'z');
    Liste * fusion2 = fusion(A, creerListe());
    Test(premier(fusion2) == 'a' && 
    premier(reste(fusion2)) == 'f' && 
    premier(reste(reste(fusion2))) == 'g' && 
    premier(reste(reste(reste(fusion2)))) == 'u' && 
    premier(reste(reste(reste(reste(fusion2))))) == 'z'
    , "Fusion de la liste A (non vide) avec la liste B (vide).");


    // Liste A vide 
    Liste * fusion3 = fusion(A, B);
    Test(premier(fusion3) == 'a' && 
    premier(reste(fusion3)) == 'c' && 
    premier(reste(reste(fusion3))) == 'e' && 
    premier(reste(reste(reste(fusion3)))) == 'f' && 
    premier(reste(reste(reste(reste(fusion3))))) == 'g' &&
    premier(reste(reste(reste(reste(reste(fusion3)))))) == 'g' &&
    premier(reste(reste(reste(reste(reste(reste(fusion3))))))) == 'k' &&
    premier(reste(reste(reste(reste(reste(reste(reste(fusion3)))))))) == 'o' &&
    premier(reste(reste(reste(reste(reste(reste(reste(reste(fusion3))))))))) == 'q' &&
    premier(reste(reste(reste(reste(reste(reste(reste(reste(reste(fusion3)))))))))) == 'u' &&
    premier(reste(reste(reste(reste(reste(reste(reste(reste(reste(reste(fusion3))))))))))) == 'z'
    , "Fusion de la liste A (vide) avec la liste B (non vide).");








    // Test de libération de la mémoire avec 'valgrind --leak-check=full ./<executable>'
    libererListe(l1);
    libererListe(l1Bis);
    libererListe(l2);

    libererListe(A);
    libererListe(B);

    libererListe(fusion1);
    libererListe(fusion2);
    libererListe(fusion3);
}