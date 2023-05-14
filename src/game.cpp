#include"game.h"

// erase an element of a vector
template<class T>
void unorderErase(std::vector<T>& arr, int i){
    arr[i] = arr.back();
    arr.pop_back();
}

void Game::clearScreen(){
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(gRenderer);
}

void Game::init(){
    // set size of map
    mapWidth = 34, mapHeight = 28;
    map.setSize(mapWidth, mapHeight);

    gameMode = _1_PLAYER;
    quit = false;
    score = 0;
    hightScore = 0;

    if(! SDLInit(GAME_NAME)){
        printf("SDL khong the khoi tao!\n");
        return ;
    }

    // man hinh ban dau
    menuTexture.loadFromFile("images/menu/start_menu.png", SDL_FALSE);
    for(int i = 1; i <= menuTexture.getHeight(); i += 3){
        clearScreen();
        SDL_Rect curMenu = {0, 0, menuTexture.getWidth(), i};
        menuTexture.render(0, SCREEN_HEIGHT - i, &curMenu);
        SDL_RenderPresent(gRenderer);
        delay();
    }

    selectionClip = {0, 0, 28, 28};
    selection.loadFromFile("images/tanks/tank1.png", SDL_TRUE);

    map.init();
    Tank::init();
    srand(time(NULL));
}

// show main menu to screen 
void Game::showMenu(){
    menuTexture.render(0, 0, NULL);
    if(gameMode == _1_PLAYER){
        selection.renderEx(128, 228, &selectionClip, 90, NULL);
    }
    else if(gameMode == _2_PLAYER){
        selection.renderEx(128, 254, &selectionClip, 90, NULL);
    }
    else if(gameMode == CONSTRUCTION){
        selection.renderEx(128, 280, &selectionClip, 90, NULL);
    }
}

void test(){
    std::vector<Explosion> explosions;
    explosions.push_back(Explosion(100, 100, Explosion::SMALL_EXPLOSION));
    explosions.push_back(Explosion(200, 200, Explosion::BIG_EXPLOSION));
    explosions.back().setPos(200, 200);
    explosions.back().setType(Explosion::BIG_EXPLOSION);

    for(Explosion explosion: explosions){
        explosion.render();
        printf("explosion render!\n");
    }
}

Game::Game(){
    init();

    // game loop
    while(! quit){
        clearScreen();

        test();
        
        update();

        SDL_RenderPresent(gRenderer);
        delay();
    }

    SDLExit();
}

Game::~Game(){
    SDLExit();
}

void Game::update(){
    updateInput();
    if(gameInput.type == Input::SHIFT) {
        gameMode = GAME_MODE((gameMode + 1) % GAME_MODES_TOTAL);
        gameInput.clear();
    }
    else if(gameInput.type == Input::K){
        printf("KKK");
        gameInput.clear();
        if(gameMode == _1_PLAYER) {
            onePlayer();
        }
        else if(gameMode == _2_PLAYER){
            twoPlayers();
        }
    }
    showMenu();
}

void Game::updateInput(){
    while(SDL_PollEvent(&event) != 0){
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

void Game::delay(){
    std::this_thread::sleep_for(std::chrono::milliseconds(FRAME_DELAY));
}

void Game::objectsRender(){
    // printf("Render all objects!\n");
}

void Game::onePlayer(){
    printf("One player mode\n");
    SDL_RenderClear(gRenderer);

    if(! map.loadMapFromFile("data/map.txt")){
        printf("Unable to load map.txt\n");
        return;
    }

    printf("Loaded map\n");

    // set player's tank
    Tank player;
    player.setTankColor(Tank::YELLOW);
    player.setDirection(UP);
    player.setPosition(0, 0);
    player.setSpeed(3);

    bullets.clear();

    while(! quit && ! isGameOver()){
        updateInput();
        clearScreen();

        player.step(&gameInput, &map, &bullets);
        gameInput.clear();
        
        enemiesUpdate();
        player.render();
        bulletsUpdate();


        map.render();
        scoreRender();
        objectsRender();

        SDL_RenderPresent(gRenderer);
        delay();
    }
}

void Game::twoPlayers(){
    
}

void Game::bulletsUpdate(){

    // va cham voi ke dich
    for(int i = 0; i < bullets.size(); i ++){
        bool colide = false;
        bullets[i].move();

        for(int j = 0; j < enemies.size(); j ++){
            if(bullets[i].hasCollision(enemies[j].getRect())){
                colide = true;

                printf("Bullet colide a tank!\n");

                // destroy block if it isn't an iron block...
                unorderErase(enemies, j --);
            }
        }
        if(colide){
            unorderErase(bullets, i --);
        }
    }
    
    // va cham voi cac block
    for(int i = 0; i < bullets.size(); i ++){
        bool colide = false;

        std::vector<Block>* blocks = map.getBlocks();

        for(int j = 0; j < blocks->size(); j ++){
            if(blocks->at(j).getCanColide() && bullets[i].hasCollision(blocks->at(j).getRect())){
                colide = true;

                // destroy block if it isn't an iron block...
                if(blocks->at(j).getBlockType() != Block::BlockType::IRON) {
                    if(blocks->at(j).getBlockType() == Block::FLAG) {
                        blocks->at(j).setBlockType(Block::BROKEN_FLAG);
                    }
                    else unorderErase(*blocks, j --);
                }
            }
        }

        if(colide || ! map.isInMap(bullets[i].getRect())){
            unorderErase(bullets, i --);
            continue;
        }

        bullets[i].render();
    }

    // update enemyBillets

    for(int i = 0; i < enemyBullets.size(); i ++){
        bool colide = false;
        enemyBullets[i].move();

        std::vector<Block>* blocks = map.getBlocks();

        for(int j = 0; j < blocks->size(); j ++){
            if(blocks->at(j).getCanColide() && enemyBullets[i].hasCollision(blocks->at(j).getRect())){
                colide = true;

                // destroy block if it isn't an iron block...
                if(blocks->at(j).getBlockType() != Block::BlockType::IRON) {
                    unorderErase(*blocks, j);
                    j --;
                }
            }
        }

        if(colide || ! map.isInMap(enemyBullets[i].getRect())){
            unorderErase(enemyBullets, i --);
            continue;
        }

        enemyBullets[i].render();
    }
}


void Game::spawnEnemy(SDL_Rect spawnArea){
    bool ok = false;

    while(! ok){
        ok = true;
        printf("Created an enemy tank!\n");
        int x = spawnArea.x + rand() % (spawnArea.w - Tank::TANK_SIZE + 1);
        int y = spawnArea.y + rand() % (spawnArea.h - Tank::TANK_SIZE + 1);
        int color = rand() % 5 + 2;
        for(Enemy enemy: enemies){
            if(enemy.hasCollision({x, y, Tank::TANK_SIZE, Tank::TANK_SIZE})) ok = false;
        }

        if(! ok) continue;

        enemies.push_back(Enemy());
        printf("Pushed\n");
        enemies.back().setPosition(x, y);
        enemies.back().setDirection(RIGHT);
        enemies.back().setTankColor(Tank::TankColor(color));
        enemies.back().setSpeed(2);
    }
}

void Game::enemiesUpdate(){
    // spawn new enemy
    if(SDL_GetTicks() - lastSpawnTime >= ENEMY_SPAWN_DELAY_TIME){
        lastSpawnTime = SDL_GetTicks();
        spawnEnemy({0, 0, map.getWidth() * Block::SMALL_BLOCK_SIZE, 2 * Block::SMALL_BLOCK_SIZE});
    }

    for(Enemy &enemy: enemies){
        enemy.step(&map, &enemyBullets);
        printf("ENEMY speed: %d\n", enemy.getSpeed());
    }

    // render enemies
    for(Enemy enemy: enemies){
        enemy.render();
    }
}

bool Game::isGameOver(){
    std::vector<Block> *blocks = map.getBlocks();
    for(int i = 0; i < blocks->size(); i ++){
        if(blocks->at(i).getBlockType() == Block::FLAG) return false;
    }
    return true;
}

void Game::scoreRender(){
    SDL_Color textColor = {255, 255, 255};
    Texture sc;
    sc.loadFromRenderedText("Score !", textColor);
    sc.render(600, 300, NULL);
}