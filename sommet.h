#ifndef SOMMET_H
#define SOMMET_H

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <queue>
#include "arete.h"

class Sommet
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(std::string,double,double);
        void ajouterVoisin(const Sommet*,Arete*);
        void afficherData() const;
        void afficherVoisins() const;
        void displayPath(std::string id) const;
        void setPaths(std::unordered_map<std::string, std::string> p);
        std::vector<const Sommet*> getVoisins() const;
        std::vector<std::string> getVoisinsId() const;
        std::set<Arete*> getAretesAdjacents();
        std::string getId() const;
        double getX() const;
        double getY() const;
        int getDeg() const;
        ~Sommet();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;
        std::set<Arete*> m_aretesAdjacent;
        std::unordered_map<std::string, std::string> m_paths;

        /// Donn�es sp�cifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
