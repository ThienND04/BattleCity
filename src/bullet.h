#ifndef BULLET_H

#define BULLET_H
#include"object.h"
#include"texture.h"

class Bullet: public Object{
public:
    static const int BULLET_SIZE = 8;
    static const int BULLET_SPEED = 4;
    Bullet(int x, int y, Direction direction);
    ~Bullet();

    void render();

    // free resource
    void free();

    bool hasCollision(SDL_Rect otherObject);

    SDL_Rect getRect();

private:

    // for render
    Texture texture;
    SDL_Rect clip;
};

static const std::string bulletImgPath = "images/bullet/bullet.png";

#endif