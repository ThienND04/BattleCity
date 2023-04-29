#include"game.h"

void Game::clearScreen(){
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(gRenderer);
}

void Game::init(){
    quit = false;
    score = 0;
    hightScore = 0;

    if(! SDLInit(GAME_NAME)){
        printf("SDL khong the khoi tao!\n");
    }
}

// show main menu to screen 
void Game::showMenu(){
    menuTexture.loadFromFile("images/menu/start_menu.png", SDL_FALSE);

    for(int i = 1; i <= menuTexture.getHeight(); i += 3){
        clearScreen();
        SDL_Rect curMenu = {0, 0, menuTexture.getWidth(), i};
        menuTexture.render(0, SCREEN_HEIGHT - i, &curMenu);
        SDL_RenderPresent(gRenderer);
        std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
    }
}

Game::Game(){
    init();

    showMenu();

    // game loop
    while(! quit){
        updateInput();
    }
}

Game::~Game(){
    SDLExit();
}

void Game::updateInput(){
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            gameInput.type = Input::QUIT;
            quit = true;
        }
        else if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym)
            {
            case SDLK_a: 
                gameInput.type = Input::A;
                break;
            case SDLK_w: 
                gameInput.type = Input::W;
                break;
            case SDLK_d: 
                gameInput.type = Input::D;
                break;
            case SDLK_s: 
                gameInput.type = Input::S;
                break;
            case SDLK_k: 
                gameInput.type = Input::K;
                break;
            case SDLK_LSHIFT: 
                gameInput.type = Input::SHIFT;
                break;
            case SDLK_RSHIFT: 
                gameInput.type = Input::SHIFT;
                break;
            }
        }
    }
}

