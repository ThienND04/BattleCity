#ifndef BULLET_H

#define BULLET_H
#include"object.h"

class Bullet: public Object{
private:

public:
    const int speed = 10;

    Bullet(int x, int y, Direction direction);

    ~Bullet();

    void render();

    // free resource
    void free();
};

#endif