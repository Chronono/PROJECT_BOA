#include <math.h>
#include "graph.h"
#include <math.h>
#include "utilalleg.h"
#include "arete.h"
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
            m_aretes.find(id)->second->setDistance(getDistance(v1,v2));
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
        float cost1, cost2;
        fichier_weight >> id >> cost1 >> cost2;
        m_aretes.find(id)->second->setCost1(cost1);
        m_aretes.find(id)->second->setCost2(cost2);
    }

    /// fermeture du fichier_weight
    fichier_weight.close();


    /// application de Dijkstra à chaque sommets
    for (auto i : m_vertices)
        i.second->setPaths(Dijkstra(i.second->getId()));

    std::cout << "\naffiche du chemin du sommet 4 vers le sommet 0 :  ";
    m_vertices.find("0")->second->displayPath("7");

    primDistance = parcoursPrim(false);
    primCost = parcoursPrim(true);
    std::vector<std::string> test = gen_binSolution();
    m_solutionsdepareto = pareto(test);
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
        info = i.second->getId() + ": (" + std::to_string((int)i.second->getCost2()) + ";" + std::to_string((int)i.second->getCost1()) + ")";
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

void graphe::initDijkstra(std::string Vstart, std::unordered_map<std::string, Sommet*> G, std::unordered_map<std::string, int>& distances)
{
    for (auto v = G.begin(); v != G.end(); v++) {
        distances.emplace(v->second->getId(), getTotDistance());
    }
    distances.find(Vstart)->second = 0;
    /// affiche distances
    //for (auto d : distances) { std::cout << "distance de " << d.first << " par rapport a " << Vstart << " : " << d.second << std::endl; }
}

std::string graphe::findMin(std::unordered_map<std::string, Sommet*> G, std::unordered_map<std::string, int>& distances) const
{
    //std::cout << "FIND_MIN :\n";
    int mini = getTotDistance() + 1;
    //std::cout << "mini = " << mini;
    std::string v = "empty";
    //std::cout << "   v = " << v << std::endl;
    for (auto v_it = G.begin(); v_it != G.end(); v_it++) {
        if (distances.find(v_it->first)->second < mini) {
            mini = distances.find(v_it->first)->second;
            //std::cout << "mini = " << mini;
            v = v_it->first;
            //std::cout << "   v = " << v << std::endl;
        }
    }
    //std::cout << "sortie de FIND_MIN\n" << std::endl;
    return v;
}

void graphe::updateDist(std::string v1, std::string v2, std::unordered_map<std::string, int>& distances, std::unordered_map<std::string, std::string>& path)
{
    //std::cout << "UPDATE_DIST :\n";
    if (distances.find(v2)->second > distances.find(v1)->second + getDistance(v1, v2)) {
        //std::cout << "distances.find(" << v2 << ")->second > distances.find(" << v1 << ")->second + getDistance(" << v1 << ", " << v2 << ") : VRAI" << std::endl;
        distances.find(v2)->second = distances.find(v1)->second + getDistance(v1, v2);
        //std::cout << "distances.find(" << v2 << ")->second = " << distances.find(v1)->second + getDistance(v1, v2) << std::endl;
        if (!path.count(v2)) {
            path.emplace(v2,v1);
            //std::cout << "path.emplace(" << v2 << ", " << v1 << ")" << std::endl;
        }
        else {
            path.find(v2)->second = v1;
            //std::cout << "path.find(" << v2 << ")->second = " << v1 << std::endl;
        }
    }
    //else
        //std::cout << "distances.find(" << v2 << ")->second > distances.find(" << v1 << ")->second + getDistance(" << v1 << ", " << v2 << ") : FAUX" << std::endl;

    //std::cout << "sortie de UPDATE_DIST\n" << std::endl;
}

std::unordered_map<std::string, std::string> graphe::Dijkstra(std::string Vstart)
{
    //std::cout << "Lancement de Dijkstra\n" << std::endl;
    std::unordered_map<std::string, Sommet*> G = m_vertices;
    //std::cout << "nombre de sommets dans G : " << G.size() << std::endl;
    /// affiche le graphe
    //for (auto i : G) { std::cout << i.first << " / "; } std::cout << std::endl;
    std::unordered_map<std::string, int> distances;
    //if (distances.empty()) { std::cout << "'distance' est vide" << std::endl; }
    //else { std::cout << "'distance' n'est pas vide. taille = " << distances.size() << std::endl; }
    std::unordered_map<std::string, std::string> path; /// <sommet , prédécesseur>
    //if (path.empty()) { std::cout << "'path' est vide" << std::endl; }
    //else { std::cout << "'path' n'est pas vide. taille = " << path.size() << std::endl; }
    std::string v;

    //std::cout << "\nDebut de l'initialisation..." << std::endl;
    initDijkstra(Vstart, G, distances);
    //std::cout << "...Fin de l'initialisation\n" << std::endl;
    while (!G.empty()) {
        v = findMin(G, distances);
        //std::cout << "v prend " << v << std::endl;
        G.erase(v);
        /// affiche le graphe
        //for (auto i : G) { std::cout << i.first << " / "; } std::cout << std::endl;

        auto tab_id = m_vertices.find(v)->second->getVoisinsId();
        for (std::string voisinID : tab_id) {
            updateDist(v, voisinID, distances, path);
        }
        /// affiche distances
        //std::cout << "\nnouvelles distances :\n";
        //for (auto d : distances) { std::cout << "distance de " << d.first << " par rapport a " << Vstart << " : " << d.second << std::endl; }
    }
    return path;
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

double graphe::getDistance(std::string v1, std::string v2)
{
    double x1 = m_vertices.find(v1)->second->getX(),
           y1 = m_vertices.find(v1)->second->getY(),
           x2 = m_vertices.find(v2)->second->getX(),
           y2 = m_vertices.find(v2)->second->getY(),
           distance = sqrt(pow(abs((int)(x1 - x2)), 2) + pow(abs((int)(y1 - y2)), 2));

    return distance;
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

double graphe::getTotDistance() const
{
    double totDist = 0;
    for (auto a : m_aretes) {
        totDist += a.second->getDistance();
    }
    return totDist;
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

std::vector<std::string> graphe::gen_binSolution()
{
    int nbSolutions = pow(2,getSize());
    std::vector<std::string> solutions;
    for (int i=0; i < nbSolutions; i++)
        solutions.push_back(toBinary(i));

    return solutions;
}

std::vector<std::string> graphe::getGPCC(std::vector<std::string>& combinaisons)
{
    std::cout << "\nGraphes partiels couvrants connexes :\n";
    std::vector<std::string> solutions;

    /// pour chaque schéma :
    for (std::string code : combinaisons) {
        /// si le nombre de sommets conectés est égal au nombre de sommets en tout, le graphe n'est pas eulérien
        std::unordered_set<std::string> visited;
        for (unsigned int i=0; i < code.size(); i++)
        {
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
    }
    return solutions;
}

std::pair<float,float> graphe::getPoidsSolPareto(std::string code_bin){
    std::pair<float,float> poids; /// first -> distance, second -> cout
    for (int i = 0; i < code_bin.size(); i++)
    {
        char ind[m_aretes.size()];
        sprintf(ind, "%d", (code_bin.size() -1) - i);
        if (code_bin[i] == '1')
        {
            poids.first += m_aretes.find(ind)->second->getCost2();
            poids.second += m_aretes.find(ind)->second->getCost1();
        }
    }

    return poids;
}

std::vector<std::string> graphe::getFrontiereSolPareto(bool choice) /// false return dominé true dominant
{
    std::vector<std::string> tabParetoDomine;
    std::vector<std::string> tabParetoDominant;

    for (auto i : m_solutionsdepareto)
    {
        std::cout << "Debug #1 -> boucle sol Pareto\n";
        if (tabParetoDominant.empty()==true){
            tabParetoDominant.push_back(i);
            std::cout << "Debug #2 -> pas de dominant, on ajoute le refentiel dominant\n";
        }
        else
        {
            std::pair<float,float> poidTest = getPoidsSolPareto(i);
            //for (auto j : tabParetoDominant)
            size_t sizeDominantInstantT = tabParetoDominant.size();
            bool placed = false;
            while (placed == false){
            for (int j = 0; j < sizeDominantInstantT; j++)
            {
                std::cout << "Debug #3 -> j : " << j << " < " << sizeDominantInstantT << std::endl;
                std::pair<float,float> poidDominant = getPoidsSolPareto(tabParetoDominant[j]);
                std::cout << "Debug #4 -> boucle dominante + poidSolPareto : (" << poidTest.first << "," << poidTest.second << "), poid du dominant : (" << poidDominant.first << "," << poidDominant.second << ")" << std::endl;
                if (poidTest.first > poidDominant.first && poidTest.second > poidDominant.second){
                    std::cout << "Debug #5 -> solution domine\n";
                    tabParetoDomine.push_back(i);
                    placed = true;
                    break;
                    }
                else if (poidTest.first < poidDominant.first && poidTest.second < poidDominant.second)
                {
                    std::cout << "Debug #5_1 -> solution dominante\n";
                    tabParetoDominant.push_back(i);
                    tabParetoDomine.push_back(tabParetoDominant[j]);
                    tabParetoDominant.erase(tabParetoDominant.begin() + j);
                    std::cout << "Debug #5_2 -> solution dominante ajoute et domine retire\n";
                    placed=true;
                }
                else if (j == sizeDominantInstantT-1){
                    std::cout << "Debug #6 -> pas de solution dominante, donc elle meme ajoute en tant que dominant\n";
                    tabParetoDominant.push_back(i);
                    placed = true;
                }
                    /*
                else if (j == tabParetoDominant[tabParetoDominant.size()])
                {
                    tabParetoDominant.push_back(j);
                    for (int k = 0; k < tabParetoDominant.size(); k++)
                    {
                        if (tabParetoDominant[k] != j){
                            std::pair<float,float> poidDominantTest = getPoidsSolPareto(tabParetoDominant[k]);
                            if (poidDominant.first < poidDominantTest.first && poidDominant.second < poidDominantTest.second)
                            {
                                tabParetoDomine.push_back(tabParetoDominant[k]);
                                tabParetoDominant.erase(tabParetoDominant.begin() + k);
                            }
                        }
                    }
                }*/
            }
            }
        }
    }

    for (auto i : tabParetoDominant)
        std::cout << "pareto dominant : " << i << std::endl;
    if (choice==true)
        return tabParetoDominant;
    else
        return tabParetoDomine;
}

std::vector<std::string> graphe::pareto(std::vector<std::string>& combinaisons)
{
    std::cout << "\nSolutions de pareto :" << std::endl;
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
            for (unsigned int i=0; i < code.size(); i++)
            //for (int i = code.size() - 1; i >= 0; --i)
            {
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
                std::cout << code;
                int poid1=0;
                int poid2=0;
                for (unsigned int i = 0; i < code.size();i++) {
                    char ind[m_aretes.size()];
                    sprintf(ind, "%d", (code.size() -1) - i);
                    std::cout << "  ind : " << ind;
                    if (code[i] == '1'){
                    poid1 += m_aretes.find(ind)->second->getCost1();
                    poid2 += m_aretes.find(ind)->second->getCost2();
                    }
                }
                std::cout << " --> (D:" << poid1 << ",P:" << poid2 << ")"<< std::endl;
                std::pair<float,float> poids = getPoidsSolPareto(code);
                std::cout << " --> (D:" << poids.first << ",P:" << poids.second << ")"<< std::endl;
            }
        }
    }
    return paretoSolutions;
}

graphe::~graphe()
{
    //dtor
}
