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
#include"input.h"
#include"explosion.h"
#include"enemy.h"
#include<vector>

using namespace std::chrono_literals;

const std::string GAME_NAME = "Battle City";

template<class T>
void unorderErase(std::vector<T>& arr, int i);

class Game{ 
public:
    enum GAME_MODE{
        _1_PLAYER,
        _2_PLAYER,
        CONSTRUCTION, 
        GAME_MODES_TOTAL
    };

    Game();
    ~Game();

    void reset();

    bool isGameOver();

    void gameOver();

    void init();

    void clearScreen();
    void showMenu();

    void update();
    void updateInput();

    void spawnEnemy(SDL_Rect spawnArea);

    // update objects
    void bulletsUpdate();
    void enemiesUpdate();
    void explosionsUpdate();

    void delay();

    // play mode
    void onePlayer();
    void twoPlayers();

    void scoreRender();

    void gameRender();

    void playerUpdate();

    void test();

private:
    // game state
    bool quit;
    SDL_Event event;
    Input gameInput;
    GAME_MODE gameMode;
    Texture menuTexture;
    Texture selection;

    // 
    SDL_Rect selectionClip;
    
    // data
    int mapWidth;
    int mapHeight;

    Tank player;

    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<Bullet> enemyBullets;
    std::vector<Explosion> explosions;
    Map map;
    int score;
    int hightScore;

    int lastSpawnTime = 0;
    const int ENEMY_SPAWN_DELAY_TIME = 5000; // thoi gian de sinh ke dich
};
#endif