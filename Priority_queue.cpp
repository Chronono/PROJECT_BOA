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

bool compare_areteCost1(const Arete* first, const Arete* second)
{
    return (first->getCost1() < second->getCost1());
}

bool compare_areteCost2(const Arete* first, const Arete* second)
{
    return (first->getCost2() < second->getCost2());
}

void Priority_queue::add(Sommet *som, bool choice) /// si choice = false alors priority queue en fct de distance sinon fct de cost
{
    for (auto it : som->getAretesAdjacents())
    {
        m_areteTri.push_back(it);
        if (choice==false)
            m_areteTri.sort(compare_areteCost1);
        else
            m_areteTri.sort(compare_areteCost2);
    }
}
