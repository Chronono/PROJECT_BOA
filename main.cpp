#include <iostream>
#include <allegro.h>
#include "utilalleg.h"
#include "boutton.h"
#include "graph.h"
#include <string>
#include <fstream>
#include <vector>
#include <math.h>

int main()
{
    graphe testCubeTown("cubetown.txt","cubetown_weights_0.txt");
    initialisation();

    return 0;
}
END_OF_MAIN();
