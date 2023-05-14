#include"texture.h"

Texture::Texture(){
    wrapedTexture = NULL;
    height = 0;
    width = 0;
}

Texture::~Texture(){
    free();
}

bool Texture::loadFromFile(std::string path, SDL_bool colorKeying){
    SDL_Texture* newTexture = NULL;
    free();
    
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL){
        printf("Unable to load image %s! IMG Error: %s\n", path.c_str(), IMG_GetError());
    }
    else{
        // cat phan thua cua anh
        SDL_SetColorKey(loadedSurface, colorKeying, SDL_MapRGB(loadedSurface->format, 0, 0, 0));
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

bool Texture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        wrapedTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( wrapedTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            width = textSurface->w;
            height = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
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

void Texture::renderEx(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center){
    SDL_Rect renderSpace = {x, y, width, height};
    if(clip != NULL){
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, wrapedTexture, clip, &renderSpace, angle, center, SDL_FLIP_NONE);
}

void Texture::free(){
    if(wrapedTexture != NULL){
        SDL_DestroyTexture(wrapedTexture);
        wrapedTexture = NULL;
        height = 0;
        width = 0;
    }
}