#ifndef OBJECT_H

#define OBJECT_H
#include<SDL2/SDL.h>
#include"direction.h"
#include"texture.h"

class Object{
public:
    Object(){};
    Object(int x, int y, Direction direction);
    ~Object();

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

    // di chuyen
    void move();

    // xac dinh va cham
    bool hasCollision(SDL_Rect otherObject);

    void setInvisible(bool invisible);

    bool isInvisible();

private:
    int x, y;
    int width, height;
    Direction direction;
    int speed;

    bool invisible;
};

#endif