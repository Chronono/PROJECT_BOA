#include <math.h>
#include "graph.h"
#include <math.h>
#include "utilalleg.h"
#include <allegro.h>

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

    primDistance = parcoursPrim(false);
    primCost = parcoursPrim(true);

    /// génération de tous les schémasa possibles du graphe
    //std::vector<std::string> test = gen_pareto_solution();
}

void graphe::afficherPrim(std::list<Arete*> prim, int couleur){
    FONT * fontsommet = load_font("fontsommet.pcx",NULL,NULL);
    BITMAP* cercle = load_bitmap("cercle.bmp",NULL);
    double x1 = 0 , x2 = 0 ,y1 = 0 , y2 = 0, marge = 0;
for (auto i : prim) {
        for (auto j : m_vertices){
            if(j.second->getId() == i->getVertex1())
            {
                x1 = j.second->getX() + 25;
                y1 = j.second->getY() + 25;
            }
            if(j.second->getId() == i->getVertex2())
            {
                x2 = j.second->getX() + 25;
                y2 = j.second->getY() + 25;
            }
        }
        line(screen, x1, y1, x2, y2, couleur);
        textprintf_ex(screen,fontsommet,(x1+x2)/2,(y1+y2)/2,makecol(0,150,0),-1,i->getId().c_str());
    }
    for (auto i : m_vertices){
        draw_sprite(screen,cercle,i.second->getX(),i.second->getY());
        if(i.second->getId().size() == 1) marge = 20;
        else marge = 12;
        textprintf_ex(screen,fontsommet,i.second->getX() + marge,i.second->getY() + 12,makecol(0,0,0),-1,i.second->getId().c_str());
    }
}

void graphe::display() const{
    clear_to_color(screen,makecol(255,255,255));
    FONT * fontsommet = load_font("fontsommet.pcx",NULL,NULL);
    FONT * fontarete = load_font("areteId.pcx",NULL,NULL);
    BITMAP* cercle = load_bitmap("cercle.bmp",NULL);
    double x1 = 0 , x2 = 0 ,y1 = 0 , y2 = 0, marge = 0;
    std::string info;
    for (auto i : m_aretes) {
        for (auto j : m_vertices){
            if(j.second->getId() == i.second->getVertex1())
            {
                x1 = j.second->getX() + 25;
                y1 = j.second->getY() + 25;
            }
            if(j.second->getId() == i.second->getVertex2())
            {
                x2 = j.second->getX() + 25;
                y2 = j.second->getY() + 25;
            }
        }
        line(screen, x1, y1, x2, y2, makecol(0,0,0));
        textprintf_ex(screen,fontsommet,(x1+x2)/2,(y1+y2)/2,makecol(0,150,0),-1,i.second->getId().c_str());
        info = i.second->getId() + ": (" + std::to_string((int)i.second->getDistance()) + ";" + std::to_string((int)i.second->getCost()) + ")";
        textprintf_ex(screen,fontsommet,670,50+30*std::stoi(i.second->getId()),makecol(0,0,0),-1,info.c_str());
    }
    for (auto i : m_vertices){
        draw_sprite(screen,cercle,i.second->getX(),i.second->getY());
        if(i.second->getId().size() == 1) marge = 20;
        else marge = 12;
        textprintf_ex(screen,fontsommet,i.second->getX() + marge,i.second->getY() + 12,makecol(0,0,0),-1,i.second->getId().c_str());
    }
}


void graphe::AfficherDistance(){
    FONT * fontsommet = load_font("fontsommet.pcx",NULL,NULL);
    BITMAP* cercle = load_bitmap("cercle.bmp",NULL);
    double x1 = 0 , x2 = 0 ,y1 = 0 , y2 = 0, marge = 0;
    for (auto i : primDistance) {
        for (auto j : m_vertices){
            if(j.second->getId() == i->getVertex1())
            {
                x1 = j.second->getX() + 25;
                y1 = j.second->getY() + 25;
            }
            if(j.second->getId() == i->getVertex2())
            {
                x2 = j.second->getX() + 25;
                y2 = j.second->getY() + 25;
            }
        }
        line(screen, x1, y1, x2, y2, makecol(255,0,0));
        textprintf_ex(screen,fontsommet,(x1+x2)/2,(y1+y2)/2,makecol(0,150,0),-1,i->getId().c_str());
    }
    for (auto i : m_vertices){
        draw_sprite(screen,cercle,i.second->getX(),i.second->getY());
        if(i.second->getId().size() == 1) marge = 20;
        else marge = 12;
        textprintf_ex(screen,fontsommet,i.second->getX() + marge,i.second->getY() + 12,makecol(0,0,0),-1,i.second->getId().c_str());
    }
}


void graphe::AfficherCost(){
FONT * fontsommet = load_font("fontsommet.pcx",NULL,NULL);
    BITMAP* cercle = load_bitmap("cercle.bmp",NULL);
    double x1 = 0 , x2 = 0 ,y1 = 0 , y2 = 0, marge = 0;
    for (auto i : primCost) {
        for (auto j : m_vertices){
            if(j.second->getId() == i->getVertex1())
            {
                x1 = j.second->getX() + 25;
                y1 = j.second->getY() + 25;
            }
            if(j.second->getId() == i->getVertex2())
            {
                x2 = j.second->getX() + 25;
                y2 = j.second->getY() + 25;
            }
        }
        line(screen, x1, y1, x2, y2, makecol(0,0,255));
        textprintf_ex(screen,fontsommet,(x1+x2)/2,(y1+y2)/2,makecol(0,150,0),-1,i->getId().c_str());
    }
    for (auto i : m_vertices){
        draw_sprite(screen,cercle,i.second->getX(),i.second->getY());
        if(i.second->getId().size() == 1) marge = 20;
        else marge = 12;
        textprintf_ex(screen,fontsommet,i.second->getX() + marge,i.second->getY() + 12,makecol(0,0,0),-1,i.second->getId().c_str());
    }
}

void graphe::AfficherBoth()
{
    FONT * fontsommet = load_font("fontsommet.pcx",NULL,NULL);
    BITMAP* cercle = load_bitmap("cercle.bmp",NULL);
    double x1 = 0 , x2 = 0 ,y1 = 0 , y2 = 0, marge = 0;

    for (auto i : primDistance) {
        for (auto j : m_vertices){
            if(j.second->getId() == i->getVertex1())
            {
                x1 = j.second->getX() + 25;
                y1 = j.second->getY() + 25;
            }
            if(j.second->getId() == i->getVertex2())
            {
                x2 = j.second->getX() + 25;
                y2 = j.second->getY() + 25;
            }
        }
        for(auto k : primCost)
        {
            if(i->getId() == k->getId())
            {
                line(screen, x1, y1, x2, y2, makecol(0,255,0));
            }
        }
        textprintf_ex(screen,fontsommet,(x1+x2)/2,(y1+y2)/2,makecol(0,150,0),-1,i->getId().c_str());
    }


    for (auto i : m_vertices){
        draw_sprite(screen,cercle,i.second->getX(),i.second->getY());
        if(i.second->getId().size() == 1) marge = 20;
        else marge = 12;
        textprintf_ex(screen,fontsommet,i.second->getX() + marge,i.second->getY() + 12,makecol(0,0,0),-1,i.second->getId().c_str());
    }
}


std::list<Arete*> graphe::parcoursPrim(bool choice){        /// choice = false, prim fct distance sinon fct cost
    Priority_queue listArete;
    std::list<Arete*> primArete;
    std::set<Sommet*> sommetsVisited;
    Sommet* toVisit = m_vertices.find("0")->second;
    Arete* areteTmp;

    while (sommetsVisited.size() != getOrder())
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

/// SOURCE DU CODE DU CONVERTISSEUR BINAIRE : INTERNET (+ modifications personnelles) ///
std::string graphe::toBinary(int n)
{
    std::cout << n << " convert to ";
    std::string r;
    /// j'ai ajouter la condition r.size() < 8 afin de limiter la taille de la chaine renvoyée, j'ai choisit 8 car un octet correspond à 8 bits
    while (n!=0 && r.size() < 8) {
        r = (n%2 == 0 ? "0":"1") + r;
        n/=2;
    }
    /// cette boucle sert à compléter la chaine afin de toujours renvoyer un résultat homogène
    while (r.size() < 8) {
        r = "0" + r;
    }
    std::cout << r << std::endl;

    return r;
}

std::vector<std::string> graphe::gen_pareto_solution()
{
    int nbSolutions = (int)pow(2, getSize());
    std::vector<std::string> solutions;
    for (int i=0; i < nbSolutions; i++)
        solutions.push_back(toBinary(i));

    return solutions;
}

graphe::~graphe()
{
    //dtor
}
