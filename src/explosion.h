#ifndef EXPLOSION_H

#define EXPLOSION_H


#include"texture.h"

class Explosion{
public:
    enum Type{
        SMALL_EXPLOSION,
        BIG_EXPLOSION
    };

    Explosion(int x, int y, Type exType);
    
    ~Explosion();

    void setPos(int x, int y);

    int getExSize();

    // set exploside type
    void setType(Type exType);

    void render();

private:
    int x, y;
    int exSize;
    Texture texture;
};

#endif