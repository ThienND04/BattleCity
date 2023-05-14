#include"tank.h"

Texture tanksTexture;

Tank::Tank(){
    
}

Tank::Tank(int x, int y, Direction direction){
    setPosition(x, y);
    setDirection(direction);
}

Tank::~Tank(){
    // printf("Destroy tank!\n");
}

void Tank::shot(std::vector<Bullet>* bullets){
    // printf("Shot ----------------\n");
    // tao 1 vien dan o khoi tiep theo cua duong di 
    bullets->push_back(Bullet(getX() + TANK_SIZE / 2, getY() + TANK_SIZE / 2, getDirection()));

    // doan nay kthem vao de set lai bullet ( khong biet sao cac gia tri lai bien thanh random ...)
    bullets->back().setDirection(getDirection());
    bullets->back().setSpeed(Bullet::BULLET_SPEED);
    
    if(getDirection() % 2 == 0) {
        bullets->back().setPosition(getX() + (TANK_SIZE - Bullet::BULLET_SIZE) / 2, getY() + getDirection() * TANK_SIZE / 2);
    }
    else {
        bullets->back().setPosition(getX() + (int(getDirection()) % 3) * TANK_SIZE / 2, getY() + (TANK_SIZE - Bullet::BULLET_SIZE) / 2);
    }
}

void Tank::step(Input* input, Map* map, std::vector<Bullet>* bullets){
    if(input->type == Input::NONE) return;
    if(input->type == Input::K) {
        shot(bullets);
        // printf("Bullets's size: %d\n", bullets->size());
        // printf("push back ok\n");
    }
    else{
        if(input->type == Input::W) setDirection(Direction::UP);
        else if(input->type == Input::D) setDirection(Direction::RIGHT);
        else if(input->type == Input::S) setDirection(Direction::DOWN);
        else if(input->type == Input::A) setDirection(Direction::LEFT);
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
                printf("Colide!!\n");
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

void Tank::render(){
    tanksTexture.renderEx(getX(), getY(), &clip, 90 * getDirection(), NULL);
}

void Tank::setTankColor(TankColor color){
    // load
    //texture.loadFromFile(TANKS_PATH, SDL_FALSE);

    this->color = color;

    // update clip
    clip = {0, 0, TANK_SIZE, TANK_SIZE};
    if(color == YELLOW) {
        clip.x = 2 * TANK_SIZE;
        clip.y = 4 * TANK_SIZE;
    }
    else if(color == GREEN){
        clip.x = 0;
        clip.y = 4 * TANK_SIZE;
    }
    else if(color == RED){
        clip.x = 6 * TANK_SIZE;
        clip.y = 0 * TANK_SIZE;
    }
    else if(color == GRAY){
        clip.x = 0;
        clip.y = 0;
    }
    else if(color == PINK){
        clip.x = 2 * TANK_SIZE;
        clip.y = 0;
    }
}

bool Tank::hasCollision(SDL_Rect otherObject){
    SDL_Rect rect1 = {getX(), getY(), TANK_SIZE, TANK_SIZE};
    return SDL_HasIntersection(&rect1, &otherObject);
}

SDL_Rect Tank::getRect(){
    return {getX(), getY(), TANK_SIZE, TANK_SIZE};
}

void Tank::init(){
    tanksTexture.loadFromFile(TANKS_PATH, SDL_TRUE);
}