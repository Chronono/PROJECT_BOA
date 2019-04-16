#include <iostream>
#include "graph.h"

std::string toBinary(int n)
{
    std::string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

int main()
{
    graphe testCubeTown("cubetown.txt","cubetown_weights_0.txt");
    testCubeTown.display();

    std::cout << "\n\nPrim : \n     En fonction de la distance" << std::endl;
    displayList(testCubeTown.parcoursPrim(false));
    std::cout << "\n\n      En fonction du cout" << std::endl;
    displayList(testCubeTown.parcoursPrim(true));

    std::cout << "\n\n7 en binaire : " << toBinary(7);
}
