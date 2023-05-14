#include"map.h"

Map::Map(){};
Map::~Map(){};

void Map::setSize(int nWidth, int nHeight){
    width = nWidth;
    height = nHeight;
}

int Map::getWidth(){
    return width;
}

int Map::getHeight(){
    return height;
}

std::vector<Block>* Map::getBlocks(){
    return &blocks;
}

void Map::render(){
    // printf("Blocks's size: %d\n", blocks.size());
    for(Block block: blocks){
        block.render();
    }
}

void Map::init(){
    blocksInit();
}

bool Map::loadMapFromFile(std::string path){
    // readfile 
    std::ifstream fi(path);
    std::string tmp;
    while(fi >> tmp) data.push_back(tmp);
    fi.close();

    if(data.size() != height) {
        printf("Map %s is invalid! \n");
        return false;
    }
    for(unsigned int i = 0; i < data.size(); i ++){
        if(data[i].size() != width) {
            printf("Map %s is invalid! \n");
            return false;
        }
    }

    // create blocks
    for(int y = 0; y < data.size(); y ++){
        for(int x = 0; x < data[y].size(); x ++){
            switch (data[y][x])
            {
            case Block::RED_BRICK:
                blocks.push_back(Block(x * Block::SMALL_BLOCK_SIZE, y * Block::SMALL_BLOCK_SIZE, Block::RED_BRICK));
                break;
            case Block::IRON:
                blocks.push_back(Block(x * Block::SMALL_BLOCK_SIZE, y * Block::SMALL_BLOCK_SIZE, Block::IRON));
                break;
            case Block::GLASSES:
                blocks.push_back(Block(x * Block::SMALL_BLOCK_SIZE, y * Block::SMALL_BLOCK_SIZE, Block::GLASSES));
                break;
            case Block::ICE:
                blocks.push_back(Block(x * Block::SMALL_BLOCK_SIZE, y * Block::SMALL_BLOCK_SIZE, Block::ICE));
                break;
            case Block::FLAG: 
                // printf("rendering flag\n");
                if(data[y - 1][x] != data[y][x] && data[y][x - 1] != data[y][x]) {
                    blocks.push_back(Block(x * Block::SMALL_BLOCK_SIZE, y * Block::SMALL_BLOCK_SIZE, Block::FLAG));
                }
                break;
            case Block::BROKEN_FLAG:
                if(data[y - 1][x] != data[y][x] && data[y][x - 1] != data[y][x]) {
                    blocks.push_back(Block(x * Block::SMALL_BLOCK_SIZE, y * Block::SMALL_BLOCK_SIZE, Block::BROKEN_FLAG));
                }
                break;
            }
        }
    }

    return true;
}

bool Map::isInMap(SDL_Rect objRect){
    return objRect.x >= 0 && objRect.y >= 0 && \
        objRect.x + objRect.w <= width * Block::SMALL_BLOCK_SIZE - 1 && objRect.y + objRect.h <= height * Block::SMALL_BLOCK_SIZE - 1;
}