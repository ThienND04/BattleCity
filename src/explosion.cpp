#include"explosion.h"

Explosion::Explosion(int x, int y, Type exType){
    setPos(x, y);
    setType(exType);
}

Explosion::~Explosion(){
    //texture.free();
}

void Explosion::setPos(int x, int y){
    this->x = x;
    this->y = y;
}

int Explosion::getExSize(){
    return exSize;
}

void Explosion::setType(Type exType){
    if(exType == SMALL_EXPLOSION){
        texture.loadFromFile("images/animation/explosion1.png", SDL_FALSE);
        exSize = texture.getWidth();
    }
    else if(exType == BIG_EXPLOSION){
        texture.loadFromFile("images/animation/explosion2.png", SDL_FALSE);
        exSize = texture.getHeight();
    }
}

void Explosion::render(){
    texture.render(x, y, NULL);
}