#ifndef TEXTURE_H 

#define TEXTURE_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include"lib.h"

class Texture{
public:
    Texture();
    ~Texture();

    bool loadFromFile(std::string path, SDL_bool colorKeying);

    //Creates image from font string
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    
    void render(int x, int y, SDL_Rect* clip);
    void renderEx(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center);
    void free();

    // get image dimensions
    int getWidth();
    int getHeight();

private:
    int width;
    int height;
    SDL_Texture* wrapedTexture;
};

#endif