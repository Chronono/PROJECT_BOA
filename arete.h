#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <vector>
#include<string>

class Arete
{
public:
    Arete(std::string id, std::string v1, std::string v2);
    std::string getId() const;
    std::vector<std::string> getVertices() const; /// retourne les indices des sommets sous forme de pair
    std::string getVertex1() const;
    std::string getVertex2() const;
    void setDistance(float);
    void setCost(float);
    float getDistance() const;
    float getCost() const;
    ~Arete();
private:
    std::string m_id;
    std::string m_vertex1; /// sommet 1
    std::string m_vertex2; /// sommet 2
    float m_distance;
    float m_cost;
};

#endif // ARETE_H_INCLUDED
