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

    int MovementDirection = 2;
    int mode = 1;   //currently mode = 0 for idle, mode = 1 for walk

    AIController() = default;

    AIController(int direction, int entity_mode){
        MovementDirection = direction;
        mode = entity_mode;
    }

    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override{
        if(mode == 1){
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



        else if(mode == 0){
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