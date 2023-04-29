#ifndef GAME_H

#define GAME_H 

#include<iostream>
#include<thread>
#include<chrono>
#include"lib.h"
#include"map.h"
#include"tank.h"
#include"bullet.h"
#include"texture.h"
#include<vector>

using namespace std::chrono_literals;

const std::string GAME_NAME = "Battle City";

class Game{ 
public:
    struct Input{
        enum Type{
            QUIT, 
            // move
            A, 
            W, 
            S,
            D, 
            K, // Enter
            SHIFT // change chosen 
        };
        Type type;
    };

    Game();
    ~Game();

    void init();

    void clearScreen();
    void showMenu();

    void update();

    void updateInput();

private:
    // game state
    bool quit;
    SDL_Event event;
    Input gameInput;
    Texture menuTexture;
    Tank player;
    
    // data
    std::vector<Tank> enemies;
    Map map;
    int score;
    int hightScore;
};
#endif