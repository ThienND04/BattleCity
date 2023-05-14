#ifndef TANK_H

#define TANK_H
#include<SDL2/SDL_image.h>
#include<iostream>
#include"texture.h"
#include"object.h"
#include"bullet.h"
#include"map.h"
#include"input.h"

class Tank: public Object{
public:
    static const int TANK_SIZE = 28;
    enum TankColor{
        YELLOW,
        GREEN,
        GRAY,
        PINK,
        RED
    };

    static void init();

    Tank();
    Tank(int x, int y, Direction direction);

    ~Tank();

    void shot(std::vector<Bullet>* bullets);
    void step(Input* input, Map* map, std::vector<Bullet>* bullets);
    void render();

    void setTankColor(TankColor color);

    bool hasCollision(SDL_Rect otherObject);

    SDL_Rect getRect();

private:
    // render
    TankColor color;
    SDL_Rect clip;
};

extern Texture tanksTexture;
static std::string TANKS_PATH = "images/tanks/tanks.png";

#endif