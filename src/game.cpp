#include"game.h"

// erase an element of a vector
template<class T>
void unorderErase(std::vector<T>& arr, int i){
    arr[i] = arr.back();
    arr.pop_back();
}

void Game::clearScreen(){
    // SDL_SetRenderDrawColor(gRenderer, 149, 149, 149, 0xFF);
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

void Game::test(){
    // std::vector<Explosion> explosions;
    // explosions.push_back(Explosion(100, 100, Explosion::SMALL_EXPLOSION));
    // // explosions.push_back(Explosion(200, 200, Explosion::BIG_EXPLOSION));
    // explosions.back().setPos(200, 200);
    // explosions.back().setType(Explosion::SMALL_EXPLOSION);

    // for(Explosion& explosion: explosions){
    //     explosion.render();
    //     // printf("explosion pos: %d %d\n", explosion.getX(), explosion.getY());
    // }
    // Texture att;
    // att.loadFromFile("images/animation/big_explosion_1.png", SDL_TRUE);

    // att.render(200, 200, NULL);
}

Game::Game(){
    init();

    // game loop
    while(! quit){
        clearScreen();
        
        update();

        // test();

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
    reset();
    printf("One player mode\n");
    SDL_RenderClear(gRenderer);

    if(! map.loadMapFromFile("data/map.txt")){
        printf("Unable to load map.txt\n");
        return;
    }

    printf("Loaded map\n");

    while(! quit && ! isGameOver()){
        updateInput();
        clearScreen();

        playerUpdate();
        gameInput.clear();
        
        enemiesUpdate();
        player.render();
        bulletsUpdate();
        explosionsUpdate();


        map.render();
        scoreRender();
        objectsRender();

        SDL_RenderPresent(gRenderer);
        delay();
    }

    if(isGameOver()){
        gameOver();
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

                // printf("Bullet colide a tank!\n");

                // destroy block if it isn't an iron block...

                explosions.push_back(Explosion(enemies[j].getX(), enemies[j].getY(), Explosion::BIG_EXPLOSION));

                explosions.back().setPos(enemies[j].getX() + (Enemy::TANK_SIZE - explosions.back().getExSize()) / 2 + 1,\
                        enemies[j].getY() + (Enemy::TANK_SIZE - explosions.back().getExSize()) / 2 + 1);
                explosions.back().setType(Explosion::BIG_EXPLOSION);

                unorderErase(enemies, j --);

                // increase score
                score += 100;
            }
        }
        if(colide){
            // printf("Create an explosion!\n");
            explosions.push_back(Explosion(bullets[i].getX(), bullets[i].getY(), Explosion::SMALL_EXPLOSION));

            explosions.back().setPos(bullets[i].getX() + (Bullet::BULLET_SIZE - explosions.back().getExSize()) / 2 + 1,\
                        bullets[i].getY() + (Bullet::BULLET_SIZE - explosions.back().getExSize()) / 2 + 1);
            explosions.back().setType(Explosion::SMALL_EXPLOSION);
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
            explosions.push_back(Explosion(bullets[i].getX(), bullets[i].getY(), Explosion::SMALL_EXPLOSION));

            explosions.back().setType(Explosion::SMALL_EXPLOSION);
            explosions.back().setPos(bullets[i].getX() + (Bullet::BULLET_SIZE - explosions[i].getExSize()) / 2 + 1,\
                        bullets[i].getY() + (Bullet::BULLET_SIZE - explosions.back().getExSize()) / 2 + 1);

            unorderErase(bullets, i --);
            continue;
        }

        bullets[i].render();
    }

    // update enemyBullets

    for(int i = 0; i < enemyBullets.size(); i ++){
        bool colide = false;
        enemyBullets[i].move();

        std::vector<Block>* blocks = map.getBlocks();

        for(int j = 0; j < blocks->size(); j ++){
            if(blocks->at(j).getCanColide() && enemyBullets[i].hasCollision(blocks->at(j).getRect())){
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

        if(colide || ! map.isInMap(enemyBullets[i].getRect())){
            explosions.push_back(Explosion(enemyBullets[i].getX(), enemyBullets[i].getY(), Explosion::SMALL_EXPLOSION));

            explosions.back().setType(Explosion::SMALL_EXPLOSION);
            explosions.back().setPos(enemyBullets[i].getX() + (Bullet::BULLET_SIZE - explosions[i].getExSize()) / 2 + 1,\
                        enemyBullets[i].getY() + (Bullet::BULLET_SIZE - explosions.back().getExSize()) / 2 + 1);
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

        if(enemy.hasCollision(player.getRect())){
            // printf("Colide!!\n");
            if(enemy.getDirection() == Direction::LEFT){
                enemy.setPosition(player.getX() + Tank::TANK_SIZE, enemy.getY());
            }
            else if(enemy.getDirection() == Direction::RIGHT){
                enemy.setPosition(player.getX() - Tank::TANK_SIZE, enemy.getY());
            }
            else if(enemy.getDirection() == Direction::UP){
                enemy.setPosition(enemy.getX(), player.getY() + Tank::TANK_SIZE);
            }
            else if(enemy.getDirection() == Direction::DOWN){
                enemy.setPosition(enemy.getX(), player.getY() - Tank::TANK_SIZE);
            }
        }
        // printf("ENEMY speed: %d\n", enemy.getSpeed());
    }

    // render enemies
    for(Enemy enemy: enemies){
        enemy.render();
    }
}

void Game::explosionsUpdate(){
    int curTime = SDL_GetTicks();
    for(int i = 0; i < explosions.size(); i ++){
        if(explosions[i].isFinish()){
            unorderErase(explosions, i --);
        }
        else {
            explosions[i].render();
        }
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
    Texture sc, hsc;
    hsc.loadFromRenderedText("High score", textColor);
    sc.loadFromRenderedText(std::to_string(score), textColor);
    // printf("%d\n", (SCREEN_WIDTH + Block::SMALL_BLOCK_SIZE * map.getWidth() - sc.getWidth()) / 2);

    hsc.render((SCREEN_WIDTH + Block::SMALL_BLOCK_SIZE * map.getWidth() - hsc.getWidth()) / 2,\
         (SCREEN_HEIGHT - hsc.getHeight()) / 3, NULL);

    sc.render((SCREEN_WIDTH + Block::SMALL_BLOCK_SIZE * map.getWidth() - sc.getWidth()) / 2,\
         (SCREEN_HEIGHT - sc.getHeight()) / 2, NULL);
}

void Game::playerUpdate(){
    player.step(&gameInput, &map, &bullets);

    for(Enemy enemy: enemies){
        if(player.hasCollision(enemy.getRect())){
            // printf("Colide!!\n");
            if(player.getDirection() == Direction::LEFT){
                player.setPosition(enemy.getX() + Tank::TANK_SIZE, player.getY());
            }
            else if(player.getDirection() == Direction::RIGHT){
                player.setPosition(enemy.getX() - Tank::TANK_SIZE, player.getY());
            }
            else if(player.getDirection() == Direction::UP){
                player.setPosition(player.getX(), enemy.getY() + Tank::TANK_SIZE);
            }
            else if(player.getDirection() == Direction::DOWN){
                player.setPosition(player.getX(), enemy.getY() - Tank::TANK_SIZE);
            }
        }
    }
}

void Game::reset(){
    // set player's tank
    player.setTankColor(Tank::YELLOW);
    player.setDirection(UP);
    player.setPosition(300, 423);
    player.setSpeed(4);

    enemies.clear();
    bullets.clear();
    enemyBullets.clear();
    explosions.clear();
}

void Game::gameOver(){
    Texture gameOverTexture;
    SDL_Color textColor = {0xFF, 0, 0, 0xFF};
    gameOverTexture.loadFromRenderedText("GAME OVER", textColor);

    for(int y = map.getHeight() * Block::SMALL_BLOCK_SIZE; y >= (map.getHeight() * Block::SMALL_BLOCK_SIZE - gameOverTexture.getHeight()) / 2; y --){
        clearScreen();

        gameOverTexture.render((map.getWidth() * Block::SMALL_BLOCK_SIZE - gameOverTexture.getWidth()) / 2, y, NULL);
        SDL_RenderPresent(gRenderer);
        delay();
    }

    gameOverTexture.loadFromFile("images/game_over.bmp", SDL_TRUE);
    for(int i = 1; i <= 255; i ++){
        clearScreen();

        map.render();
        gameOverTexture.render((map.getWidth() * Block::SMALL_BLOCK_SIZE - gameOverTexture.getWidth()) / 2, \
                                (map.getHeight() * Block::SMALL_BLOCK_SIZE - gameOverTexture.getHeight()) / 2, NULL);

        SDL_RenderPresent(gRenderer);
        delay();
    }
}