#include <iostream>
#include "graph.h"
<<<<<<< HEAD
#include <math.h>
=======
>>>>>>> c871c7b9f70dc1798f64d6e60800bada012ec4cc

int nbSolutions(int bits)
{
<<<<<<< HEAD
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



=======
    graphe testCubeTown("broadway.txt","broadway_weights_0.txt");

    return 0;
>>>>>>> c871c7b9f70dc1798f64d6e60800bada012ec4cc
}
