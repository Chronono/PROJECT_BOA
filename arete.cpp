#include "arete.h"

Arete::Arete(std::string id, std::string v1, std::string v2):
    m_id(id), m_vertex1(v1), m_vertex2(v2)
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

void Arete::data() const
{
    std::cout << m_id << " : (sommet 1, sommet 2) = (" << m_vertex1 << ", " << m_vertex2 << ")\n";
}

float Arete::getDistance() const
{
    return m_distance;
}

float Arete::getCost() const
{
    return m_cost;
}

void Arete::setDistance(float dist){
    m_distance = dist;
}
void Arete::setCost(float cost){
    m_cost = cost;
}

Arete::~Arete()
{

}
