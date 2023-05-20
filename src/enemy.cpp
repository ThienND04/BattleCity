#include"enemy.h"

Enemy::Enemy(){
    lastTime = 0;
    actionTime = 500;
    srand(SDL_GetTicks());
}

Enemy::~Enemy(){}

void Enemy::step(Map* map, std::vector<Bullet>* bullets){
    if(SDL_GetTicks() - lastTime >= actionTime){
        lastTime = SDL_GetTicks();

        action.type = Input::Type(rand() % 5 + 1);
    }

    if(action.type == Input::K || canShot()){
        if(canShot()) shot(bullets);
        lastTime -= actionTime;
    }
    else{
        if(cnt % DELAY_CLIP == 0){
            SDL_Rect curClip = getClip();
            if(cnt / DELAY_CLIP == 0) {
                curClip.x += TANK_SIZE;
            }
            else{
                curClip.x -= TANK_SIZE;
            }
            setClip(curClip);
        }
        cnt = (cnt + 1) % (DELAY_CLIP * 2);

        if(action.type == Input::W) setDirection(Direction::UP);
        else if(action.type == Input::D) setDirection(Direction::RIGHT);
        else if(action.type == Input::S) setDirection(Direction::DOWN);
        else if(action.type == Input::A) setDirection(Direction::LEFT);
        move();

        // di chuyen ra ngoai map ??
        setPosition(std::max(getX(), 0), std::max(getY(), 0));
        setPosition(std::min(getX(), map->getWidth() * Block::SMALL_BLOCK_SIZE - TANK_SIZE), std::min(getY(), map->getHeight() * Block::SMALL_BLOCK_SIZE - TANK_SIZE));

        // xu li va cham va di chuyen khong hop le
        std::vector<Block>* blocks = map->getBlocks();
        
        for(int i = 0; i < blocks->size(); i ++) {
            Block block = blocks->at(i);
            SDL_Rect blockRect = block.getRect();
            if(block.getCanColide() && hasCollision(blockRect)){
                // printf("Colide!!\n");
                if(getDirection() == Direction::LEFT){
                    setPosition(block.getX() + block.getBlockSize(), getY());
                }
                else if(getDirection() == Direction::RIGHT){
                    setPosition(block.getX() - TANK_SIZE, getY());
                }
                else if(getDirection() == Direction::UP){
                    setPosition(getX(), block.getY() + block.getBlockSize());
                }
                else if(getDirection() == Direction::DOWN){
                    setPosition(getX(), block.getY() - TANK_SIZE);
                }
            }
        }
    }
}