#include "arete.h"

Arete::Arete(std::string id, std::string v1, std::string v2, float distance, float cost):
    m_vertex1(v1), m_vertex2(v2), m_distance(distance), m_cost(cost)
{

}

std::string Arete::getId() const
{
    return m_id;
}

std::vector<std::string> Arete::getVertices() const
{
    return std::vector<std::string> {m_vertex1, m_vertex2};
}

std::string Arete::getVertex1() const
{
    return m_vertex1;
}

std::string Arete::getVertex2() const
{
    return m_vertex2;
}

float Arete::getDistance() const
{
    return m_distance;
}

float Arete::getCost() const
{
    return m_cost;
}

Arete::~Arete()
{

}
