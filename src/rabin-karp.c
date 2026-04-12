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

int main()
{
    char* texte = "123456789012345678901234567890123456789012345678901234567890";
    char* motif = "901";

    clock_t debut = clock();
    int pos = rabinKarp(texte, motif);
    clock_t fin = clock();

    if (pos <= (int)strlen(texte))
    {
        printf("Trouvé en position %d\n", pos);
    } else
    {
        printf("Pas trouvé\n");
    }

    printf("Rabin Karp : %f secondes\n", (double)(fin - debut) / CLOCKS_PER_SEC);
    return 0;
}