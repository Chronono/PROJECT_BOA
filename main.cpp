#include <iostream>
#include "graph.h"


int main()
{
    graphe testCubeTown("cubetown.txt","cubetown_weights_0.txt");
    testCubeTown.display();

    std::cout << "\n\nPrim : \n     En fonction de la distance" << std::endl;
    displayList(testCubeTown.parcoursPrim(false));
    std::cout << "\n\n      En fonction du cout" << std::endl;
    displayList(testCubeTown.parcoursPrim(true));
}
