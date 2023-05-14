#ifndef BLOCK_H

#define BLOCK_H

#include<SDL2/SDL.h>
#include "texture.h"
#include "lib.h"
#include"block.h"
#include<iostream>

class Block{
public:
    static const int SMALL_BLOCK_SIZE = 16;

    enum BlockType{
        NONE,
        RED_BRICK = '1',
        IRON = '2',
        GLASSES = '3',
        ICE = '4',
        FLAG = 'f', 
        BROKEN_FLAG = 'b'
    };
    Block();
    
    Block(int x, int y, BlockType blockType);

    ~Block();

    void setBlockType(BlockType blockType);
    BlockType getBlockType();

    void render();

    void resize(int newSize);

    int getBlockSize();

    int getX();
    int getY();
    void setPosition(int x, int y);

    // get the area will be render on the screen
    SDL_Rect getRect();

    bool getCanColide();
    void setCanColide(bool canColide);

private:
    // thuoc tinh block
    int x, y;
    int BLOCK_SIZE;
    BlockType blockType;
    bool canColide; // co the va cham ?
    
    SDL_Rect clip;
};

const std::string blockImgsPath = "images/blocks/blocks.png";

extern Texture blocksTexture;

void blocksInit();

#endif