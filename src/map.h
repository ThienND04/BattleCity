#ifndef MAP_H

#define MAP_H
#include<SDL2/SDL.h>

class Map{
public:
    void setSize(int nWidth, int nHeight);
    int getWidth();
    int getHeight();

    bool isValid(int x, int y);
    void render();
    
private:
    int width;
    int height;
};

#endif 