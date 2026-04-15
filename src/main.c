#define DEBUG

#include "Liste.h"


int main()
{
    #ifdef DEBUG
        testPile();
        testListe();
    #endif
    
    return 0;
}
