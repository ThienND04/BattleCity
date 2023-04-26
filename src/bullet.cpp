#include"bullet.h"

Bullet::Bullet(int x, int y, Direction direction){
    setPosition(x, y);
    setDirection(direction);
    setSpeed(speed);
}

Bullet::~Bullet(){
    free();
}

void Bullet::render(){
    printf("Rendering this bullet\n");
}

void Bullet::free(){
    printf("Free bullet\n");
}