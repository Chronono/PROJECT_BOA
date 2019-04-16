#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

#include "sommet.h"
#include "arete.h"
#include <list>

void displayList(std::list<Arete*>);

class Priority_queue
{
public:
    Priority_queue();
    ~Priority_queue();

    std::list<Arete*> getList();

    void add(Sommet*, bool);
    Arete* frontPop();

private:
    std::list<Arete*> m_areteTri;
};

#endif // PRIORITY_QUEUE_H_INCLUDED
