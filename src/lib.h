#ifndef LIB_H

#define LIB_H
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include<SDL2/SDL_ttf.h>
#include<iostream>

// luu cac thong so va cac du lieu de tuong tac voi he thong
// extern const int FPS;
// extern const int FRAME_DELAY;

// extern const int SCREEN_WIDTH = 600;
// extern const int SCREEN_HEIGHT = 442;

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 450;

extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern TTF_Font* gFont;

bool SDLInit(std::string title);

void SDLExit();

#endif