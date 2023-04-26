#ifndef TANK_H

#define TANK_H
#include"object.h"
#include"bullet.h"

class Tank: public Object{
private:
    
public:
    Bullet* shot();
    void step();
    void render();
};

#endif