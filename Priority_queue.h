#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

#include "sommet.h"
#include "arete.h"
#include <forward_list>


class Priority_queue
{
public:
    Priority_queue();
    ~Priority_queue();

    void add(Sommet*, bool);
    Arete* frontPop();

private:
    std::forward_list<Arete*> m_areteTri;
};

#endif // PRIORITY_QUEUE_H_INCLUDED
