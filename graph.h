#ifndef GRAPHE_H
#define GRAPHE_H
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "sommet.h"
#include <list>
#include <set>
#include "arete.h"
#include "Priority_queue.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string,std::string);
        ~graphe();
        void display() const;
        void displayParetoSolutions();
        std::list<Arete*> parcoursPrim(bool);
        int getOrder() const;
        int getSize() const;
        int isEulerien() const;

    protected:

    private:
        /// functions
        void gen_pareto_solution();

        /// attributes
        std::unordered_map<std::string,Sommet*> m_vertices;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Arete*> m_aretes;
        std::vector<std::string> m_pareto_solutions;
};

#endif // GRAPHE_H
