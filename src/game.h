#ifndef GAME_H

#define GAME_H 

#include"map.h"
#include"tank.h"
#include"bullet.h"
#include<list>


class Game{ 
private:
    Tank player;
    std::list<Tank> enemies;
    Map map;
    int score;

public:
    void init();

    char inputKey();
};
#endif