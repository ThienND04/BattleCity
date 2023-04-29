#ifndef OBJECT_H

#define OBJECT_H
#include<SDL2/SDL.h>
#include"direction.h"

class Object{
public:
    void setPosition(int x, int y);
    int getX();
    int getY();

    void setSize(int _width, int _height);
    int getWidth();
    int getHeight();

    void setDirection(Direction newDirection);
    Direction getDirection();

    void setSpeed(int newSpeed);
    int getSpeed();

    void move();
    void render();

private:
    int x, y;
    int width, height;
    Direction direction;
    int speed;
};

#endif