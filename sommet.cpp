#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"


Sommet::Sommet(std::string id,double x,double y):
    m_id(id),m_x(x),m_y(y)
{
}

void Sommet::ajouterVoisin(const Sommet* voisin,Arete* areteAdjacent){
    m_voisins.push_back(voisin);
    m_aretesAdjacent.emplace(areteAdjacent);
}
 void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
     std::cout << "nb arete : " << m_aretesAdjacent.size() << std::endl;
 }

void Sommet::afficherVoisins() const{
    std::cout<<"  voisins :"<<std::endl;
    for(auto v:m_voisins) {
        std::cout << "   ";
        v->afficherData();
    }
}

void Sommet::setPaths(std::unordered_map<std::string, std::string> p)
{
    m_paths = p;
}

void Sommet::displayPath(std::string id) const
{
    if (m_paths.count(id)) {
        std::cout << m_paths.find(id)->first << " ---> ";
        displayPath(m_paths.find(id)->second);
    }
    else
        std::cout << id << std::endl;
}

std::set<Arete*> Sommet::getAretesAdjacents(){
    return m_aretesAdjacent;
}

std::string Sommet::getId() const{
    return m_id;
}
std::vector<const Sommet*> Sommet::getVoisins() const{
    return m_voisins;
}

std::vector<std::string> Sommet::getVoisinsId() const
{
    std::vector<std::string> ids;
    for (auto v : m_voisins) {
        ids.push_back(v->getId());
    }
    return ids;
}

double Sommet::getX() const
{
    return m_x;
}

double Sommet::getY() const
{
    return m_y;
}

int Sommet::getDeg() const{
    return m_voisins.size();
}


Sommet::~Sommet()
{
    //dtor
}
