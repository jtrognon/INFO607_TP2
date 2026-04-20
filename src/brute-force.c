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