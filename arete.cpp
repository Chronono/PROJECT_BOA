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

float Arete::getCost1() const
{
    return m_cost1;
}

float Arete::getCost2() const
{
    return m_cost2;
}

double Arete::getDistance() const
{
    return m_distance;
}

void Arete::setCost1(float cost){
    m_cost1 = cost;
}

void Arete::setCost2(float cost){
    m_cost2 = cost;
}

void Arete::setDistance(double dist)
{
    m_distance = dist;
}

void Arete::display() const{
    std::cout<< "arete number "<< m_id <<"\n(sommet " << m_vertex1 << " to sommet " << m_vertex2 << ")\ncost1 : " << m_cost1 << " and cost2 : " << m_cost2 << std::endl;
}

Arete::~Arete()
{

}
