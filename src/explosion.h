#ifndef EXPLOSION_H

#define EXPLOSION_H


#include"texture.h"

class Explosion{
public:
    static const int CLIP_DELAY = 5;

    std::string smallExPath[3] = {
        "images/animation/small_explosion_1.png",
        "images/animation/small_explosion_2.png",
        "images/animation/small_explosion_3.png"
    };

    std::string bigExPath[5] = {
        "images/animation/big_explosion_1.png",
        "images/animation/big_explosion_2.png",
        "images/animation/big_explosion_3.png",
        "images/animation/big_explosion_4.png",
        "images/animation/big_explosion_5.png"
    };

    enum Type{
        SMALL_EXPLOSION,
        BIG_EXPLOSION
    };

    Explosion(int x, int y, Type exType);
    
    ~Explosion();

    void setPos(int x, int y);
    int getX();
    int getY();

    int getExSize();

    void setType(Type exType);

    Type getType();

    void render();

    bool isFinish();

private:
    Type exType;
    int x, y;
    int startTime;
    int cnt;
    int exSize;

    bool finish;
    Texture texture;
};

#endif