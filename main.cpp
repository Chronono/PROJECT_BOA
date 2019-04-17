#include <iostream>
#include "graph.h"
#include <math.h>

int nbSolutions(int bits)
{
    if (bits-1 > 0)
        return nbSolutions(bits-1) + pow(2,bits-1);
    else
        return 1;
}

int main()
{
    graphe testCubeTown("cubetown.txt","cubetown_weights_0.txt");
/*
    std::cout << "\n\nPrim : \n     En fonction de la distance" << std::endl;
    displayList(testCubeTown.parcoursPrim(false));
    std::cout << "\n\n      En fonction du cout" << std::endl;
    displayList(testCubeTown.parcoursPrim(true));
    */

    std::cout << "nb sol 4 : " << nbSolutions(4);



}
