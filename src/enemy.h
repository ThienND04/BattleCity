#ifndef ENEMY_H

#define ENEMY_H

#include<iostream>
#include<vector>
#include"tank.h"
#include"bullet.h"

class Enemy: public Tank{
public:

    Enemy();
    ~Enemy();

    void step(Map* map, std::vector<Bullet>* bullets);

private:
    int actionTime;
    int lastTime;

    Input action;
};

#endif