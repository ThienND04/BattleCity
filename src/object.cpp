#include"object.h"

Object::Object(int x, int y, Direction direction){
    setPosition(x, y);
    setDirection(direction);
}

Object::~Object(){
    
}

void Object::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

int Object::getX(){
    return x;
}

int Object::getY(){
    return y;
}

void Object::setSize(int _width, int _height){
    width = _width;
    height = _height;
}

int Object::getWidth(){
    return width;
}
int Object::getHeight(){
    return height;
}

void Object::setDirection(Direction newDirection){
    direction = newDirection;
}

Direction Object::getDirection(){
    return direction;
}

void Object::setSpeed(int newSpeed){
    speed = newSpeed;
}
int Object::getSpeed(){
    return speed;
}

void Object::move(){
    switch(direction) {
        case Direction::UP:
            setPosition(x, y - speed);
            break;
        case Direction::RIGHT:
            setPosition(x + speed, y);
            break;
        case Direction::DOWN:
            setPosition(x, y + speed);
            break;
        case Direction::LEFT:
            setPosition(x - speed, y);
            break;
    }
}