#include "Priority_queue.h"

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

void Priority_queue::add(Sommet *som, bool choice) /// si choice = false alors priority queue en fct de distance sinon fct de cost
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
                    m_areteTri.emplace_after(it_comp,*it);
                    placed = true;
                }
                else if (choice == false){
                    if ((**it).getDistance() < (**it_comp).getDistance()){
                        m_areteTri.emplace_after(it_comp,*it);
                        placed = true;
                    }
                }
                else if (choice == true){
                    if ((**it).getCost() < (**it_comp).getCost()){
                        m_areteTri.emplace_after(it_comp,*it);
                        placed = true;
                    }
                }
                else
                    it_comp++;
            }
        }

        it++;
    }
}

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
                    m_areteTri.emplace_after(it_comp,*it);
                    placed = true;
                }
                else if ((**it).getDistance() < (**it_comp).getDistance()){
                    m_areteTri.emplace_after(it_comp,*it);
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
