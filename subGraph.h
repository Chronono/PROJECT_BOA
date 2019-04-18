#ifndef SUBGRAPH_H_INCLUDED
#define SUBGRAPH_H_INCLUDED

#include <set>
#include <list>
#include <unordered_map>
#include <string>
#include "arete.h"
#include "sommet.h"

class graphe;

class SubGraph
{
public:
    SubGraph(std::list<Arete*>, std::string, std::unordered_map<std::string,Sommet*>);

private:
    std::string m_binaire;

    std::set<std::string> m_vertices;

    std::list<std::string> m_aretes;


};

#endif // SUBGRAPH_H_INCLUDED
