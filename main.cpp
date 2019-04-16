#include <iostream>
#include "graph.h"

int main()
{
    graphe testCubeTown("cubetown.txt","cubetown_weights_0.txt");
    testCubeTown.displayParetoSolutions();
}
