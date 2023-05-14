#ifndef MAP_H

#define MAP_H
#include<SDL2/SDL.h>
#include<iostream>
#include<vector>
#include<fstream>
#include"block.h"

// None: 0
// Red brick: 1
// Glasses: 2
// Ice: 3

class Map{
public:
    Map();
    ~Map();

    void setSize(int nWidth, int nHeight);
    int getWidth();
    int getHeight();

    bool isInMap(SDL_Rect objRect);

    void init();
    bool loadMapFromFile(std::string path);

    void render();

    std::vector<Block>* getBlocks(); 
    
private:
    int width;
    int height;
    std::vector<std::string> data;

    std::vector<Block> blocks;
};

#endif 