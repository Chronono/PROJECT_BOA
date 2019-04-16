#ifndef GRAPHE_H
#define GRAPHE_H
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include "sommet.h"
#include <list>
#include <set>
#include "arete.h"
#include "Priority_queue.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        graphe(std::string,std::string);
        ~graphe();
        void display() const;

        std::list<Arete*> parcoursPrim(bool);

        int getOrdre() const;

        int isEulerien() const;

    protected:

    private:

        std::unordered_map<std::string,Sommet*> m_vertices;//stock�e dans une map (cl�=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Arete*> m_aretes;

};

#endif // GRAPHE_H