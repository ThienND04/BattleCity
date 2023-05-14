#include"bullet.h"

Bullet::Bullet(int x, int y, Direction direction){
    Object(x, y, direction);
    printf("Bullet init!\n");
    texture.loadFromFile(bulletImgPath, SDL_TRUE);
    setSpeed(BULLET_SPEED);

    clip = {direction * BULLET_SIZE, 0, BULLET_SIZE, BULLET_SIZE};
}

Bullet::~Bullet(){
    free();
}

void Bullet::render(){
    texture.loadFromFile(bulletImgPath, SDL_FALSE);
    texture.render(getX(), getY(), &clip);
}

void Bullet::free(){
    // printf("Free bullet\n");
    texture.free();
}


bool Bullet::hasCollision(SDL_Rect otherObject){
    SDL_Rect rect1 = {getX(), getY(), BULLET_SIZE, BULLET_SIZE};
    return SDL_HasIntersection(&rect1, &otherObject);
}

SDL_Rect Bullet::getRect(){
    return {getX(), getY(), BULLET_SIZE, BULLET_SIZE};
}