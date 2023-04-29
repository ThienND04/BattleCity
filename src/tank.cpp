#include"tank.h"

Bullet* Tank::shot(){
    // tao 1 vien dan o khoi tiep theo cua duong di 
    Bullet bullet = Bullet(getX(), getY(), getDirection());
    
    return &bullet;
}

void Tank::step(){
    
}

void Tank::render(){
    printf("Rendering this tank \n");
}