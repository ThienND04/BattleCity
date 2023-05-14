#include"block.h"

Texture blocksTexture;

Block::Block(){};

Block::Block(int x, int y, BlockType blockType){
    setPosition(x, y);
    setBlockType(blockType);
}

Block::~Block(){
    
}

void Block::setBlockType(BlockType blockType){
    clip = {0, 0, BLOCK_SIZE, BLOCK_SIZE};

    resize(SMALL_BLOCK_SIZE);
    this->blockType = blockType;
    canColide = true;

    if(blockType == RED_BRICK){
        clip.x = 0;
    }
    else if(blockType == IRON){
        clip.x = SMALL_BLOCK_SIZE * 2; 
    }
    else if(blockType == GLASSES){
        clip.x = SMALL_BLOCK_SIZE * 4;
        canColide = false;
    }
    else if(blockType == ICE) {
        clip.x = SMALL_BLOCK_SIZE * 6;
        canColide = false;
    }
    else if(blockType == FLAG) {
        clip.x = SMALL_BLOCK_SIZE * 10; 
        resize(SMALL_BLOCK_SIZE * 2);
    }
    else if(blockType == BROKEN_FLAG){
        clip.x = SMALL_BLOCK_SIZE * 12; 
        resize(SMALL_BLOCK_SIZE * 2);
    }
}

void Block::render(){
    blocksTexture.render(x, y, &clip);
}

void Block::resize(int newSize){
    BLOCK_SIZE = newSize;
    clip.w = BLOCK_SIZE;
    clip.h = BLOCK_SIZE;
}

int Block::getBlockSize(){
    return BLOCK_SIZE;
}

void Block::setPosition(int x, int y){
    this->x = x;
    this->y = y;
}

int Block::getX(){
    return x;
}

int Block::getY(){
    return y;
}

void blocksInit(){
    blocksTexture.loadFromFile(blockImgsPath, SDL_TRUE);
}

void Block::setCanColide(bool canColide){
    this->canColide = canColide;
}

bool Block::getCanColide(){
    return canColide;
}

SDL_Rect Block::getRect(){
    return {x, y, BLOCK_SIZE, BLOCK_SIZE};
}

Block::BlockType Block::getBlockType(){
    return blockType;
}