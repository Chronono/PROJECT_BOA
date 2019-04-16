
#include "graph.h"

graphe::graphe(std::string nom_fichier,std::string nom_fichier_weight)
{
    /// ouverture du fichier
    std::ifstream fichier("files/" + nom_fichier);

    if (fichier)
    {
        int order;
        fichier >> order;
        for (int i=0; i < order; i++) {
            std::string id;
            int x,y;
            fichier >> id >> x >> y;
            m_sommets.emplace(id, new Sommet(id,x,y));
        }

        int size;
        fichier >> size;
        for (int i=0; i < size; i++) {
            std::string id, v1, v2;
            fichier >> id >> v1 >> v2;
            m_aretes.emplace(id, new Arete(id,v1,v2));
            m_sommets.find(v1)->second->ajouterVoisin(m_sommets.find(v2)->second);
            m_sommets.find(v2)->second->ajouterVoisin(m_sommets.find(v1)->second);
        }
    }
    else
        std::cout << "impossible d'ouvrir le fichier : " << nom_fichier << std::endl;

    /// fermeture du fichier
    fichier.close();



    /// ouverture du fichier_weight
    std::ifstream fichier_weight("files/" + nom_fichier_weight);
    int size, nbDim;
    fichier_weight >> size >> nbDim;
    for (int i=0; i < size; i++) {
        std::string id;
        float distance, cost;
        fichier_weight >> id >> distance >> cost;
        m_aretes.find(id)->second->setDistance(distance);
        m_aretes.find(id)->second->setCost(cost);
    }

    /// fermeture du fichier_weight
    fichier_weight.close();
}

void graphe::display() const{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<" Ordre : " << getOrdre() <<std::endl;
    for (auto i : m_vertices){
        std::cout<<" Sommet : "<< i.second->getId() << std::endl;
        i.second->afficherVoisins();
    }
}

std::list<Arete*> graphe::parcoursPrim(bool choice){        /// choice = false, prim fct distance sinon fct cost
    Priority_queue listArete;
    std::list<Arete*> primArete;
    std::set<Sommet*> sommetsVisited;
    Sommet* toVisit;
    Arete* areteTmp;

    while (sommetsVisited.size() != getOrdre())
    {
        listArete.add(toVisit,choice);
        areteTmp = listArete.frontPop();

        while((sommetsVisited.count(m_vertices.find(areteTmp->getVertex1())->second)==true)&&(sommetsVisited.count(m_vertices.find(areteTmp->getVertex2())->second)==true))
            areteTmp = listArete.frontPop();

        if(sommetsVisited.count(m_vertices.find(areteTmp->getVertex1())->second)==true)
            toVisit = m_vertices.find(areteTmp->getVertex2())->second;
        else
            toVisit = m_vertices.find(areteTmp->getVertex1())->second;

        sommetsVisited.insert(sommetsVisited.begin(),toVisit);
        primArete.push_back(areteTmp);
    }
}

int graphe::getOrdre() const{
    return m_vertices.size();
}
int graphe::isEulerien() const{
    int compt=0;
    for (auto i : m_vertices)
        if ((i.second)->getDeg()%2 == 1)
            compt++;
    if (compt == 0)
        return 2;
    else if (compt == 2)
        return 1;
    else return 0;
}

graphe::~graphe()
{
    //dtor
}