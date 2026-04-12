#include "../headers/brute-force.h"

int bruteForce(char* texte, char* motif)
{
    int i = 0;
    int m = strlen(texte);
    int n = strlen(motif);
    bool trouve = false; 
    int res;

    while (!trouve && i <= m-n)
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
        if (!trouve)
        {
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
    int pos = bruteForce(texte, motif);
    clock_t fin = clock();

    if (pos <= (int)strlen(texte))
    {
        printf("trouvé en position %d\n", pos);
    } else
    {
        printf("pas trouvé\n");
    }

    printf("Brute Force : %f secondes\n", (double)(fin - debut) / CLOCKS_PER_SEC);
    return 0;
}