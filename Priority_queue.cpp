#include "Priority_queue.h"

void displayList(std::list<Arete*> listArete)
{
    for (auto it : listArete)
    {
        it->display();
    }
}

Priority_queue::Priority_queue(){

}

Priority_queue::~Priority_queue(){

}

Arete* Priority_queue::frontPop()
{
    Arete* poidMinArete = m_areteTri.front();
    m_areteTri.pop_front();
    return poidMinArete;
}

std::list<Arete*> Priority_queue::getList()
{
    return m_areteTri;
}

bool compare_areteDist(const Arete* first, const Arete* second)
{
    return (first->getDistance() < second->getDistance());
}

bool compare_areteConst(const Arete* first, const Arete* second)
{
    return (first->getCost() < second->getCost());
}

void Priority_queue::add(Sommet *som, bool choice) /// si choice = false alors priority queue en fct de distance sinon fct de cost
{
    int compt=0;
    for (auto it : som->getAretesAdjacents())
    {
        m_areteTri.push_back(it);
        if (choice==false)
            m_areteTri.sort(compare_areteDist);
        else
            m_areteTri.sort(compare_areteConst);
    }
}
/*
void Priority_queue::add(Sommet *som, bool choice) /// si choice = false alors priority queue en fct de distance sinon fct de cost
{
    std::set<Arete*>::iterator it = som->getAretesAdjacents().begin();
    int compt=0;
    while (it != som->getAretesAdjacents().end())
    {
        std::cout << "quelle tour de boucle ? : " << compt << std::endl;
        std::cout << "combien d'aretes dans aretetri : "<< m_areteTri.size() << std::endl;
        displayList(m_areteTri);
        if (m_areteTri.empty() == true)
        {
            m_areteTri.push_front(*it);
        }
        else
        {
            std::list<Arete*>::iterator it_comp = m_areteTri.begin();
            bool placed = false;
            while (placed==false)
            {
                if (it_comp == m_areteTri.end()){
                    m_areteTri.push_back(*it);
                    placed = true;
                }
                else if (choice == false){
                    if ((**it).getDistance() < (**it_comp).getDistance()){
                        m_areteTri.insert(it_comp,*it);
                        placed = true;
                    }
                }
                else if (choice == true){
                    if ((**it).getCost() < (**it_comp).getCost()){
                        m_areteTri.emplace(it_comp,*it);
                        placed = true;
                    }
                }

                it_comp++;

            }
        }

        it++;
        compt++;
    }
}
*/
/*
void Priority_queue::add(Sommet *som)
{
    std::set<Arete*>::iterator it = som->getAretesAdjacents().begin();
    while (it != som->getAretesAdjacents().end())
    {
        if (m_areteTri.empty() == true)
        {
            m_areteTri.emplace_front(*it);
        }
        else
        {
            std::forward_list<Arete*>::iterator it_comp = m_areteTri.begin();
            bool placed = false;
            while (placed==false)
            {
                if (it_comp == m_areteTri.end()){
                    m_areteTri.emplace(it_comp,*it);
                    placed = true;
                }
                else if ((**it).getDistance() < (**it_comp).getDistance()){
                    m_areteTri.emplace(it_comp,*it);
                    placed = true;
                }
                else
                    it_comp++;
            }
        }

        it++;
    }
}
*/
