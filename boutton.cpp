#include <iostream>
#include "boutton.h"

boutton::boutton(){
}

boutton::~boutton(){
}

void boutton::modifyboutton(int x, int y, std::string ligne){
    this->m_x = x;
    this->m_y = y;
    this->m_ligne = ligne;
}

int boutton::getX(){
    return this->m_x;
}

int boutton::getY(){
    return this->m_y;
}

std::string boutton::getLigne(){
    return this->m_ligne;
}

int boutton::getSizeLigne(){
    return this->m_ligne.size();
}
