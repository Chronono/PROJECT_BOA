#include <math.h>
#include "graph.h"
#include <math.h>

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
            m_vertices.emplace(id, new Sommet(id,x,y));
        }

        int size;
        fichier >> size;
        for (int i=0; i < size; i++) {
            std::string id, v1, v2;
            fichier >> id >> v1 >> v2;
            m_aretes.emplace(id, new Arete(id,v1,v2));
            m_vertices.find(v1)->second->ajouterVoisin(m_vertices.find(v2)->second, m_aretes.find(id)->second);
            m_vertices.find(v2)->second->ajouterVoisin(m_vertices.find(v1)->second, m_aretes.find(id)->second);
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

    /// génération de tous les schémasa possibles du graphe
    std::vector<std::string> test = gen_binSolution();
    std::vector<std::string> solutionsdepareto = pareto(test);
}

void graphe::display() const{
    std::cout<<"graphe :\n"<<std::endl;

    std::cout<<" Ordre : " << getOrder() <<std::endl;
    for (auto i : m_vertices){
        std::cout<<" Sommet ";
        i.second->afficherData();
        i.second->afficherVoisins();
    }

    std::cout << "\n Taille : " << getSize() << std::endl;
    for (auto i : m_aretes) {
        std::cout << " Arete ";
        i.second->display();
    }
}

std::list<Arete*> graphe::parcoursPrim(bool choice){        /// choice = false, prim fct distance sinon fct cost
    Priority_queue listArete;
    std::list<Arete*> primArete;
    std::set<Sommet*> sommetsVisited;
    Sommet* toVisit = m_vertices.find("0")->second;
    Arete* areteTmp;

    while ((int)sommetsVisited.size() != (int)getOrder())
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

        if (areteTmp!=primArete.front())
            primArete.push_back(areteTmp);
    }

    return primArete;
}

int graphe::getOrder() const
{
    return m_vertices.size();
}

int graphe::getSize() const
{
    return m_aretes.size();
}

int graphe::isEulerien(std::unordered_map<std::string,Sommet*> vertices) const{
    int compt=0;
    for (auto i : vertices)
        if ((i.second)->getDeg()%2 == 1)
            compt++;
    if (compt == 0)
        return 2;
    else if (compt == 2)
        return 1;
    else return 0;
}

/// SOURCE DU CODE DU CONVERTISSEUR BINAIRE : INTERNET (+ modifications personnelles) ///
std::string graphe::toBinary(int n)
{
    std::cout << n << " convert to ";
    std::string r;
    /// j'ai ajouter la condition r.size() < 8 afin de limiter la taille de la chaine renvoyée, j'ai choisit 8 car un octet correspond à 8 bits
    while (n!=0 && r.size() < m_aretes.size()) {
        r = (n%2 == 0 ? "0":"1") + r;
        n/=2;
    }
    /// cette boucle sert à compléter la chaine afin de toujours renvoyer un résultat homogène
    while (r.size() < m_aretes.size()) {
        r = "0" + r;
    }
    std::cout << r << std::endl;

    return r;
}

<<<<<<< HEAD
int nbSolutionsBin(int bits)
{
    if (bits-1 > 1)
        return nbSolutionsBin(bits-1) + pow(2,bits-1);
    else
        return 1;
}

std::vector<std::string> graphe::gen_pareto_solution()
=======
std::vector<std::string> graphe::gen_binSolution()
>>>>>>> c871c7b9f70dc1798f64d6e60800bada012ec4cc
{
    int nbSolutions = nbSolutionsBin(getSize());
    std::vector<std::string> solutions;
    for (int i=0; i < nbSolutions; i++)
        solutions.push_back(toBinary(i));

    return solutions;
}

std::vector<std::string> graphe::pareto(std::vector<std::string>& combinaisons)
{
    std::cout << "Solutions de pareto :" << std::endl;
    std::vector<std::string> paretoSolutions;

    /// pour chaque schéma :
    for (std::string code : combinaisons) {

        /// calcul du nombre d'arêtes dans le schéma
        unsigned int nbArete(0);
        for (unsigned int i=0; i < code.size(); i++)
            if (code[i] == '1')
                nbArete++;

        /// si le schéma étudier à "nbSommets-1" arêtes, alors on peux poursuivre les calculs
        if (nbArete == m_vertices.size() - 1) {
            /// si le nombre de sommets conectés est égal au nombre de sommets en tout, le graphe n'est pas eulérien
            std::unordered_set<std::string> visited;
            for (unsigned int i=0; i < code.size(); i++) {
                if (code[i] == '1') {
                    char ind[m_aretes.size()];
                    sprintf(ind,"%d",i);
                    std::string v1 = m_aretes.find(ind)->second->getVertex1();
                    std::string v2 = m_aretes.find(ind)->second->getVertex2();
                    if (!visited.count(v1))
                        visited.emplace(v1);
                    if (!visited.count(v2))
                        visited.emplace(v2);
                }
            }
            if (visited.size() == m_vertices.size()) {
                paretoSolutions.push_back(code);
                std::cout << code << std::endl;
            }
        }
    }
    return paretoSolutions;
}

graphe::~graphe()
{
    //dtor
}
