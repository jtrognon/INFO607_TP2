#include "../headers/rabin-karp.h"

int hash(char* motif, int n)
{
    int res = 0;
    for (int i=0; i<n; i++)
    {
        // Ajoute les chiffres 1 par 1
        // motif[i] - '0' -> permet de récupérer le chiffre de base (code ASCII - '0')
        res = res + (motif[i] - '0');
    }
    return res % Q;
}

int glissement(int hashPrec, char sortant, char entrant)
{
    return (hashPrec - (sortant - '0') + (entrant - '0'));
}

int rabinKarp(char* texte, char* motif)
{
    int i = 0;
    int m = strlen(texte);
    int n = strlen(motif);
    int hashMotif = hash(motif, n);
    int hashTexte = hash(texte, n);
    bool trouve = false; 
    int res;

    while (!trouve && i <= m-n)
    {
        if (hashTexte == hashMotif)
        {
            bool temp = true;
            for (int j = 0; j<n; j++)
            {
                if (texte[i+j] == motif[j])
                {
                    temp = (temp && true);
                } else 
                {
                    temp = (temp && false);
                }
            }
            trouve = temp;
        }
        if (!trouve)
        {
            hashTexte = glissement(hashTexte, texte[i], texte[i+n]);
            i++;
        }
    }

    if (trouve)
    {
        res = i;
    } else
    {
        res = m+1;
    }

    return res;
}