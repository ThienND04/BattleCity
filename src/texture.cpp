#include"texture.h"

Texture::Texture(){
    wrapedTexture = NULL;
    height = 0;
    width = 0;
}

Texture::~Texture(){
    free();
}

bool Texture::loadFromFile(std::string path){
    SDL_Texture* newTexture = NULL;
    free();
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        printf("Unable to load image %s! IMG Error: %s\n", path.c_str(), IMG_GetError());
    }
    else{
        // cat phan thua cua anh
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if(newTexture == NULL){
            printf("Unable to create Texure from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
        }
        else{
            width = loadedSurface->w;
            height = loadedSurface->h;
        }

        SDL_FreeSurface(loadedSurface);
    }

    wrapedTexture = newTexture;
    return wrapedTexture != NULL;
}

int Texture::getWidth(){
    return width;
}

int Texture::getHeight(){
    return height;
}

void Texture::render(int x, int y, SDL_Rect* clip){
    SDL_Rect renderSpace = {x, y, width, height};
    if(clip != NULL){
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, wrapedTexture, clip, &renderSpace);
}

void Texture::free(){
    if(wrapedTexture != NULL){
        SDL_DestroyTexture(wrapedTexture);
        wrapedTexture = NULL;
        height = 0;
        width = 0;
    }
}