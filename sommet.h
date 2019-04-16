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
        ///constructeur qui reçoit en params les données du sommet
        Sommet(std::string,double,double);
        void ajouterVoisin(const Sommet*,Arete*);
        void afficherData() const;
        void afficherVoisins() const;
        std::vector<const Sommet*> getVoisins() const;
        std::set<Arete*> getAretesAdjacents();
        std::string getId() const;
        int getDeg() const;
        ~Sommet();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<const Sommet*> m_voisins;
        std::set<Arete*> m_aretesAdjacent;

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position

};

#endif // SOMMET_H
