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
#include <map>

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string,std::string);
        ~graphe();
        void display() const;
        std::list<Arete*> parcoursPrim(bool);
        int getOrder() const;
        int getSize() const;
        int isEulerien() const;
        void afficherPrim(std::list<Arete*>, int);
        void AfficherDistance();
        void AfficherCost();
        void AfficherBoth();

    protected:

    private:
        /// functions
        std::string toBinary(int n);
        std::vector<std::string> gen_pareto_solution();

        /// attributes
        std::list<Arete*> primDistance;
        std::list<Arete*> primCost;
        std::unordered_map<std::string,Sommet*> m_vertices;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Arete*> m_aretes;
};

#endif // GRAPHE_H
