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

int Explosion::getX(){
    return x;
}

int Explosion::getY(){
    return y;
}


int Explosion::getExSize(){
    return exSize;
}

void Explosion::setType(Type exType){
    this->exType = exType;
    cnt = 0;
    finish = 0;
    
    if(exType == SMALL_EXPLOSION){
        texture.loadFromFile(smallExPath[cnt / CLIP_DELAY], SDL_TRUE);
        exSize = texture.getWidth();
    }
    else if(exType == BIG_EXPLOSION){
        texture.loadFromFile(bigExPath[cnt / CLIP_DELAY], SDL_TRUE);
        exSize = texture.getWidth();
    }
}


Explosion::Type Explosion::getType(){
    return exType;
}

void Explosion::render(){
    if(cnt % CLIP_DELAY == 0){
        if(exType == SMALL_EXPLOSION){
            // if(exSize == 28) return;
            texture.loadFromFile(smallExPath[cnt / CLIP_DELAY], SDL_TRUE);
            exSize = texture.getWidth();
        }
        else if(exType == BIG_EXPLOSION){
            // if(exSize == 64) return;
            texture.loadFromFile(bigExPath[cnt / CLIP_DELAY], SDL_TRUE);
            exSize = texture.getWidth();
        }
    }
    texture.render(x, y, NULL);
    cnt ++;
    
    if(exType == SMALL_EXPLOSION){
        if(cnt > CLIP_DELAY * 2) finish = 1;
    }
    else if(exType == BIG_EXPLOSION){
        if(cnt > CLIP_DELAY * 4) finish = 1;
    }
}


bool Explosion::isFinish(){
    return finish;
}