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

        printf("%c\n", premier(eCourant));
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


Liste * fusion_rec(Liste * l1, Liste * l2)
{
    /**
     * \brief Renvoie une fusion des deux listes. (version récursive)
     * \param l1 La première liste triée à fusionner.
     * \param l2 La deuxième liste triée à fusionner.
     * \return La fusion des deux listes.
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
        return prefixer(fusion_rec(reste(l1), l2), premier(l1));
    }
    else // on insère le premier élément de l2
    {
        return prefixer(fusion_rec(l1, reste(l2)), premier(l2));
    }
}


Liste * fusion_it(Liste * l1, Liste * l2)
{
    /**
     * \brief Renvoie une fusion des deux listes. (version itérative)
     * \param l1 La première liste triée à fusionner.
     * \param l2 La deuxième liste triée à fusionner.
     * \return La fusion des deux listes.
     */
    Liste * res = creerListe();
    Liste * ptInt1 = l1;
    Liste * ptInt2 = l2;

    while(!vide(ptInt1) && !vide(ptInt2))
    {
        if (premier(ptInt1) < premier(ptInt2))
        {
            res = suffixer(res, premier(ptInt1));
            ptInt1 = reste(ptInt1);
        }
        else
        {
            res = suffixer(res, premier(ptInt2));
            ptInt2 = reste(ptInt2);
        }
    }

    // Ajout des valeurs restantes
    if (vide(ptInt1))
    {
        while(!vide(ptInt2))
        {
            res = suffixer(res, premier(ptInt2));
            ptInt2 = reste(ptInt2);
        }
    }
    else
    {
        while(!vide(ptInt1))
        {
            res = suffixer(res, premier(ptInt1));
            ptInt1 = reste(ptInt1);
        }
    }

    return res;
}


Liste * ssc_it(Liste * l)
{
    /**
     * \brief Renvoie la première sous-suite croissante de la liste. (version itérative)
     * \param l Une liste d'éléments.
     * \return La sous-suite croissante de la liste.
     */
    Liste * res = creerListe();    
    Liste * ptInt = l;
    
    if (!vide(ptInt))
    {
        Element ePrecedent = premier(ptInt);
        while(!vide(ptInt) && ePrecedent <= premier(ptInt)) // ajout 
        {
            ePrecedent = premier(ptInt);
            res = suffixer(res, ePrecedent);
            
            ptInt = reste(ptInt);
        }
    }

    return res;
}


Liste * ssc_rec(Liste * l)
{
    /**
     * \brief Renvoie la première sous-suite croissante de la liste. (version récursive)
     * \param l Une liste d'éléments.
     * \return La sous-suite croissante de la liste.
     */
    if (vide(l) || vide(reste(l))) // 0 ou 1 élément
    {
        return l;
    }
    else
    {
        if (premier(l) <= premier(reste(l)))
        {
            return prefixer(ssc_rec(reste(l)), premier(l));
        } 
        else 
        {

            return prefixer(creerListe(), premier(l));
        }
    }
}


Liste * comp_it(Liste * l1, Liste * l2)
{
    /**
     * \brief Renvoie le complément de la première liste dans la deuxième. (version itérative)
     * \param l1 La première liste.
     * \param l2 La deuxième liste.
     * \return Le complément de la première liste dans la deuxième.
     */
    Liste * ptInt1 = l1;
    Liste * ptInt2 = l2;

    while (!vide(ptInt1) && !vide(ptInt2)) // Pas besoin de vérifier que l1 commence l2 car nous supposons que c'est le cas 
    {
        ptInt1 = reste(ptInt1);
        ptInt2 = reste(ptInt2);
    }

    return _copieListe(ptInt2);
}


Liste * comp_rec(Liste * l1, Liste * l2)
{
    /**
     * \brief Renvoie le complément de la première liste dans la deuxième. (version récursive)
     * \param l1 La première liste.
     * \param l2 La deuxième liste.
     * \return Le complément de la première liste dans la deuxième.
     */
    if (vide(l1) | vide(l2))
    {
        return _copieListe(l2);
    }
    else
    {
        return comp_rec(reste(l1), reste(l2));
    }
}


Liste * tri_rec(Liste * l)
{
    /**
     * \brief Tri la liste donnée par fusion. (version itérative)
     * 
     */

    Liste * l1 = ssc_rec(l);
    Liste * l2 = comp_rec(l1, l);

    if (vide(l2))
    {
        return _copieListe(l1);
    }
    else
    {
        return fusion_rec(l1, tri_rec(l2));
    }
}


Liste * tri_it(Liste * l)
{
    
    // while(!vide(l2))
    // {

    // }
    // TODO
    return l;
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
    testFusion(fusion_it);
    testFusion(fusion_rec);

    // ================= SSC =================
    testSsc(ssc_it);
    testSsc(ssc_rec);

    // ================= COMP =================
    testComp(comp_it);
    testComp(comp_rec);

    // ================= Tri =================
    testTri(tri_rec);
    testTri(tri_it);


    // Test de libération de la mémoire avec 'valgrind --leak-check=full ./<executable>'
    libererListe(l1);
    libererListe(l1Bis);
    libererListe(l2);
}


void testFusion(Liste * (fusion)(Liste *, Liste *))
{
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
    Test(
        premier(fusion3) == 'a' && 
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
        , "Fusion de la liste A (vide) avec la liste B (non vide)."
    );



    libererListe(A);
    libererListe(B);

    libererListe(fusion1);
    libererListe(fusion2);
    libererListe(fusion3);
}


void testSsc(Liste * (ssc)(Liste *))
{
    // Liste vide
    Test(ssc(creerListe()) == creerListe(), "Sous-liste croissante d'une liste vide.");

    // Liste <a, e, f, c, g, h>
    Liste * l3 = creerListe();
    l3 = suffixer(l3, 'a');
    l3 = suffixer(l3, 'e');
    l3 = suffixer(l3, 'f');
    l3 = suffixer(l3, 'c');
    l3 = suffixer(l3, 'g');
    l3 = suffixer(l3, 'h');
    
    Liste * ssc1 = ssc(l3);
    Test(
        premier(ssc1) == 'a' && 
        premier(reste(ssc1)) == 'e' && 
        premier(reste(reste(ssc1))) == 'f' &&
        vide(reste(reste(reste(ssc1)))),
        "Sous-liste croissante de <a, e, f, c, g, h>."
    );


    libererListe(l3);
    libererListe(ssc1);
}


void testComp(Liste * (comp)(Liste *, Liste *))
{
    // Liste A et B vides
    Test(vide(comp(creerListe(), creerListe())), "sous-suite complément de deux listes vides");

    // Liste A vide et B non-vide
    Liste * l4 = creerListe();
    l4 = suffixer(l4, 'r');
    l4 = suffixer(l4, 'y');
    l4 = suffixer(l4, 'f');
    l4 = suffixer(l4, 'n');
    l4 = suffixer(l4, 'd');
    l4 = suffixer(l4, 'z');

    Liste * comp1 = comp(creerListe(), l4);
    Test(
        premier(comp1) == 'r' && 
        premier(reste(comp1)) == 'y' && 
        premier(reste(reste(comp1))) == 'f' && 
        premier(reste(reste(reste(comp1)))) == 'n' && 
        premier(reste(reste(reste(reste(comp1))))) == 'd' &&
        premier(reste(reste(reste(reste(reste(comp1)))))) == 'z'
        , "sous-suite complément de A (vide) dans B (non-vide)"
    );

    // Liste A non-vide et B vide
    Liste * l5 = creerListe();
    l5 = suffixer(l5, 'r');
    l5 = suffixer(l5, 'y');
    l5 = suffixer(l5, 'f');

    Liste * comp2 = comp(l5, creerListe());
    Test(
        vide(comp2)
        , "sous-suite complément de A (vide) dans B (non-vide)"
    );

    // Liste A non-vide et B non-vide avec taille(A) > taille(B)
    Liste * comp3 = comp(l4, l5);
    Test(
        vide(comp3),
        "sous-suite complément de A (non-vide) dans B (non-vide) avec taille(A) > taille(B)"
    );

    // Liste A non-vide et B non-vide avec taille(A) < taille(B)
    Liste * comp4 = comp(l5, l4);
    Test(
        premier(comp4) == 'n' && 
        premier(reste(comp4)) == 'd' && 
        premier(reste(reste(comp4))) == 'z'
        , "sous-suite complément de A (non-vide) dans B (non-vide) avec taille(A) < taille(B)"
    );

    libererListe(l4);
    libererListe(l5);
    libererListe(comp1);
    libererListe(comp2);
    libererListe(comp3);
    libererListe(comp4);
}


void testTri(Liste * (tri)(Liste *))
{
    // Tri d'une liste vide
    Test(vide(tri(creerListe())), "Tri d'une liste vide.");

    // Tri d'une liste triée
    Liste * l1 = creerListe();
    l1 = suffixer(l1, 'a');   
    l1 = suffixer(l1, 'c');   
    l1 = suffixer(l1, 'f');   
    l1 = suffixer(l1, 'r');   
    l1 = suffixer(l1, 'v');   
    l1 = suffixer(l1, 'w');   
    l1 = suffixer(l1, 'z');


    Liste * l1Triee = tri(l1);
    Test(
        premier(l1Triee) == 'a' && 
        premier(reste(l1Triee)) == 'c' && 
        premier(reste(reste(l1Triee))) == 'f' && 
        premier(reste(reste(reste(l1Triee)))) == 'r' && 
        premier(reste(reste(reste(reste(l1Triee))))) == 'v' &&
        premier(reste(reste(reste(reste(reste(l1Triee)))))) == 'w' &&
        premier(reste(reste(reste(reste(reste(reste(l1Triee))))))) == 'z',
        "Tri d'une liste triée."
    );

    // Tri d'une liste non triée
    Liste * l2 = creerListe();
    l2 = suffixer(l2, 'c');   
    l2 = suffixer(l2, 'a');   
    l2 = suffixer(l2, 'z');
    l2 = suffixer(l2, 'v');   
    l2 = suffixer(l2, 'w');   
    l2 = suffixer(l2, 'r');   
    l2 = suffixer(l2, 'f');
    
    Liste * l2Triee = tri(l2);
    Test(
        premier(l2Triee) == 'a' && 
        premier(reste(l2Triee)) == 'c' && 
        premier(reste(reste(l2Triee))) == 'f' && 
        premier(reste(reste(reste(l2Triee)))) == 'r' && 
        premier(reste(reste(reste(reste(l2Triee))))) == 'v' &&
        premier(reste(reste(reste(reste(reste(l2Triee)))))) == 'w' &&
        premier(reste(reste(reste(reste(reste(reste(l2Triee))))))) == 'z',
        "Tri d'une liste non-triée."
    );

    libererListe(l1);
    libererListe(l1Triee);
    libererListe(l2);
    libererListe(l2Triee);
}