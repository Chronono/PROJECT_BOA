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
        std::unordered_map<std::string, std::string> Dijkstra(std::string Vstart);
        std::list<Arete*> parcoursPrim(bool);
        double getDistance(std::string v1, std::string v2);
        float getTotCost(std::string id) const;
        std::pair<float,float> getPoidsSolPareto(std::string);
        std::vector<std::string> getFrontiereSolPareto();
        int getOrder() const;
        int getSize() const;
        int isEulerien() const;
        void afficherPrim(std::list<Arete*>, int);
        void AfficherDistance();
        void AfficherCost();
        void AfficherBoth();
        int isEulerien(std::unordered_map<std::string,Sommet*> vertices) const;

    protected:

    private:
        /// functions
        double getTotDistance() const;
        std::string toBinary(int n);
        std::vector<std::string> gen_binSolution();
        std::vector<std::string> getGPCC(std::vector<std::string>& combinaisons);
        std::vector<std::string> pareto(std::vector<std::string>& combinaisons);
        std::string findMin(std::unordered_map<std::string, Sommet*> G, std::unordered_map<std::string, int>& distances) const;
        void initDijkstra(std::string Vstart, std::unordered_map<std::string, Sommet*> G, std::unordered_map<std::string, int>& distances);
        void updateDist(std::string v1, std::string v2, std::unordered_map<std::string, int>& distances, std::unordered_map<std::string, std::string>& path);

        /// attributes
        std::list<Arete*> primDistance;
        std::list<Arete*> primCost;
        std::vector<std::string> m_solutionsdepareto;
        std::unordered_map<std::string,Sommet*> m_vertices;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Arete*> m_aretes;
};

#endif // GRAPHE_H
