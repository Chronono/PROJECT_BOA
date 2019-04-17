#include <iostream>
#include "graph.h"
<<<<<<< HEAD
#include <math.h>

int main()
{
    graphe testCubeTown("broadway.txt","broadway_weights_0.txt");
    testCubeTown.display();
=======


int main()
{
    graphe testCubeTown("cubetown.txt","cubetown_weights_0.txt");
>>>>>>> 2b895b302afa507d21b2a64b20ab12605385ff2e

    std::cout << "\n\nPrim : \n     En fonction de la distance" << std::endl;
    displayList(testCubeTown.parcoursPrim(false));
    std::cout << "\n\n      En fonction du cout" << std::endl;
    displayList(testCubeTown.parcoursPrim(true));
<<<<<<< HEAD

    testCubeTown.getEverySubGraph();
=======
>>>>>>> 2b895b302afa507d21b2a64b20ab12605385ff2e
}
