#ifndef AICONTROLLER_HPP
#define AICONTROLLER_HPP

#include "Components.hpp"
#include "../game.hpp"
#include "EntityComponentSystem.hpp"
#include "TransformComponent.hpp"
#include "../Constants.hpp"

class AIController: public Component {
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    ColliderComponent *cc;
    ColliderComponent *pcc;

    int MovementDirection = 2;
    int mode = BLINKY_CHASE;   //currently mode = 0 for idle, mode = 1 for walk

    AIController() = default;

    AIController(int direction, int entity_mode){
        MovementDirection = direction;
        mode = entity_mode;
    }

    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
        cc = &entity->getComponent<ColliderComponent>();
    }

    void update() override{
        //cout<<"yo";
        int tileX = (cc->collider.x + cc->collider.w/2)/TILE_SIZE;
        int tileY = (cc->collider.y + cc->collider.h/2)/TILE_SIZE;
        int d = MovementDirection;
        //if(Game::manager->getGroup(groupPlayers).size() == 0) return;
        Entity* player = Game::manager->getGroup(groupPlayers)[0];
        if(player == nullptr) cout<<"yo\n";
        pcc = &player->getComponent<ColliderComponent>();
        
        int tileX2 = (pcc->collider.x + pcc->collider.w/2)/TILE_SIZE;
        int tileY2 = (pcc->collider.y + pcc->collider.h/2)/TILE_SIZE;

        //cout<<tileX<<" "<<tileY<<", "<<tileX2<<" "<<tileY2<<"\n";
        int dir = Game::bfs(tileY*MAZE_COLUMNS + tileX, tileY2*MAZE_COLUMNS + tileX2);
        if(mode == BLINKY_CHASE){
            if(Game::Maze->nodes[tileY][tileX]->neighbours[(d+1)%4] || Game::Maze->nodes[tileY][tileX]->neighbours[(d+3)%4]){
                switch(MovementDirection){
                    case U:
                        if(cc->collider.y + cc->collider.h/2 < tileY * TILE_SIZE + TILE_SIZE/2) MovementDirection = dir;
                        break;
                    case L:
                        if(cc->collider.x + cc->collider.w/2 < tileX * TILE_SIZE + TILE_SIZE/2) MovementDirection = dir;
                        break;
                    case D:
                        if(cc->collider.y + cc->collider.h/2 >= tileY * TILE_SIZE + TILE_SIZE/2) MovementDirection = dir;
                        break;
                    case R:
                        if(cc->collider.x + cc->collider.w/2 >= tileX * TILE_SIZE + TILE_SIZE/2) MovementDirection = dir;
                        break;

                }
            }
            switch(MovementDirection){
                case 0:
                    transform->velocity.x = 0;
                    transform->velocity.y = (-1)*PLAYER_VELOCITY;
                    sprite->Play("Walk_U");
                    break;

                case 1:
                    transform->velocity.y = 0;
                    transform->velocity.x = (-1)*PLAYER_VELOCITY;
                    sprite->Play("Walk_L");
                    //sprite->RotateDegrees = 270;
                    // sprite->spriteFlip = SDL_FLIP_HORIZONTAL;                        
                    break;

                case 3:
                    transform->velocity.y = 0;
                    transform->velocity.x = PLAYER_VELOCITY;
                    sprite->Play("Walk_R");
                    //sprite->RotateDegrees = 90;
                    break;

                case 2:
                    transform->velocity.x = 0;
                    transform->velocity.y = PLAYER_VELOCITY;
                    sprite->Play("Walk_D");
                    //sprite->RotateDegrees = 180;
                    break;
                default:
                    break;
            }
        }



        else if(mode == IDLE){
            switch(MovementDirection){
                case 0:
                    transform->velocity.x = 0;
                    transform->velocity.y = 0;
                    sprite->Play("Idle_U");
                    break;

                case 1:
                    transform->velocity.y = 0;
                    transform->velocity.x = 0;
                    sprite->Play("Idle_L");
                    //sprite->RotateDegrees = 270;
                    // sprite->spriteFlip = SDL_FLIP_HORIZONTAL;                        
                    break;

                case 3:
                    transform->velocity.y = 0;
                    transform->velocity.x = 0;
                    sprite->Play("Idle_R");
                    //sprite->RotateDegrees = 90;
                    break;

                case 2:
                    transform->velocity.x = 0;
                    transform->velocity.y = 0;
                    sprite->Play("Idle_D");
                    //sprite->RotateDegrees = 180;
                    break;
                default:
                    break;
            }
        }


    }
};

#endif