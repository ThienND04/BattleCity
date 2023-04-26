#include"map.h"

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

// xe tank co the di chuyen toi day khong
bool Map::isValid(int x, int y){
    return true;
}

void Map::render(){
    printf("----------\n");
}