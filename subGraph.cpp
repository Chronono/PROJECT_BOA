#include "subGraph.h"
#include "graph.h"

bool compare_areteId(const Arete* first, const Arete* second)
{
    return (first->getId() < second->getId());
}

SubGraph::SubGraph(std::list<Arete*> listArete, std::string val_binaire, std::unordered_map<std::string,Sommet*> sommets) : m_binaire(val_binaire)
{
    listArete.sort(compare_areteId);
    for (auto it : listArete)
    {
        for (int compt=0;compt<m_binaire.size();compt++)
        {
            char comptChar[17];
            sprintf(comptChar, "%d", compt);
            if (it->getId() == comptChar)
            {
                if(m_binaire[compt]=='1'){
                    m_aretes.push_back(it->getId());
                    if (m_vertices.count(it->getVertex1())==false)
                        m_vertices.insert(it->getVertex1());
                    if (m_vertices.count(it->getVertex2())==false)
                        m_vertices.insert(it->getVertex2());
                }
            }
        }
    }
}
