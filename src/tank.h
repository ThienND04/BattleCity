#ifndef TANK_H

#define TANK_H
#include<SDL2/SDL_image.h>
#include"object.h"
#include"bullet.h"

class Tank: public Object{
public:
    Bullet* shot();
    void step();
    void render();

private:

};

#endif