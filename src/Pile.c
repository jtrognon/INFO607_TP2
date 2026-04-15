#include "Pile.h"

Pile * creerPile()
{
    /**
     * \brief Renvoie une pile vide.
     * \return Une pile vide.
     */
    return NULL;
}

bool pile_vide(Pile * pile)
{
    /**
     * \brief Regarde si la pile est vide.
     * \param pile La pile concernée.
     * \return Vrai si la pile est vide, faux sinon.
     */
    return pile == NULL;
}

Pile * empiler(Pile * pile, void * valeur)
{
    /**
     * \brief Ajoute une liste en tête de pile.
     * \param pile La pile concernée.
     * \param valeur La valeur à empiler.
     * \return La pile avec la liste donnée en tête.
     */
    Pile * tete = (Pile *) malloc(sizeof(Pile));

    tete->valeur = valeur;
    tete->suivant = pile;

    return tete;
}


ResDepiler depiler(Pile * pile)
{
    /**
     * \brief Depile un element de la pile.
     * \param pile La pile concernée.
     * \return La pile privée de sa tête et la tête retirée.
     */
    if (pile_vide(pile))
    {
        fprintf(stderr, "depiler: La pile donnée est vide.\n");
    }

    ResDepiler res = {pile->suivant, pile->valeur};
    return res;
}




void testPile()
{
    // ================= Creer pile vide =================
    Pile * pileVide = creerPile();
    Test(pileVide == NULL, "Création d'une pile vide.");

    // ===================== Empiler =====================
    // Pile vide
    Pile * p1 = creerPile();
    int v1 = 10;
    p1 = empiler(p1, &v1);
    Test(p1->valeur == &v1 && p1->suivant == NULL, "Empiler sur une pile vide.");

    int v2 = 20;
    p1 = empiler(p1, &v2);
    Test(p1->valeur == &v2 && p1->suivant->valeur == &v1 && p1->suivant->suivant == NULL, "Empiler sur une pile non-vide.");
    
    // ===================== Depiler =====================
    // Pile vide (doit provoquer une erreur)
    // depiler(pileVide);

    // Pile à 1 élément
    ResDepiler res1 = depiler(p1->suivant);
    Test(res1.pile == NULL && res1.valeur == &v1, "Depiler sur une pile à 1 élément");

    // Pile à plus d'un élément
    ResDepiler res2 = depiler(p1);
    Test(res2.pile == p1->suivant && res2.valeur == &v2, "Depiler sur une pile à plus d'un élément");

    // =================== Pile vide ? ===================
    // Pile vide
    Test(pile_vide(pileVide), "Test de pile vide sur une pile vide.");

    // Pile non-vide
    Test(!pile_vide(p1), "Test de pile vide sur une pile non-vide.");


}