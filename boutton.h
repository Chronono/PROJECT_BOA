#ifndef BOUTTON_H_INCLUDED
#define BOUTTON_H_INCLUDED
#include <string>

class boutton{
public:
    boutton();
    void modifyboutton(int x,int y,std::string ligne);
    int getX();
    int getY();
    std::string getLigne();
    int getSizeLigne();
    ~boutton();
private:
    int m_x;
    int m_y;
    std::string m_ligne;
};

#endif // BOUTTON_H_INCLUDED
