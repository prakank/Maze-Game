#ifndef KEYBOARD_CONTROLLER_HPP
#define KEYBOARD_CONTROLLER_HPP

#include "Components.hpp"
#include "../game.hpp"
#include "EntityComponentSystem.hpp"
#include "TransformComponent.hpp"
#include "../Constants.hpp"

class KeyboardController : public Component
{
    public:
        TransformComponent *transform;
        SpriteComponent *sprite;

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();
            sprite = &entity->getComponent<SpriteComponent>();    
        }

        void update() override
        {   
            
            if(Game::event.type == SDL_KEYDOWN)
            {
                // cout << "Hey\n";
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_w:
                    case SDLK_UP:
                        transform->velocity.x = 0;
                        transform->velocity.y = (-1)*PLAYER_VELOCITY;
                        sprite->Play("Walk_U");
                        //sprite->RotateDegrees = 0;
                        // sprite->spriteFlip = SDL_FLIP_VERTICAL;
                        break;

                    case SDLK_a:
                    case SDLK_LEFT:
                        transform->velocity.y = 0;
                        transform->velocity.x = (-1)*PLAYER_VELOCITY;
                        sprite->Play("Walk_L");
                        //sprite->RotateDegrees = 270;
                        // sprite->spriteFlip = SDL_FLIP_HORIZONTAL;                        
                        break;

                    case SDLK_d:
                    case SDLK_RIGHT:
                        transform->velocity.y = 0;
                        transform->velocity.x = PLAYER_VELOCITY;
                        sprite->Play("Walk_R");
                        //sprite->RotateDegrees = 90;
                        break;

                    case SDLK_s:
                    case SDLK_DOWN:
                        transform->velocity.x = 0;
                        transform->velocity.y = PLAYER_VELOCITY;
                        sprite->Play("Walk_D");
                        //sprite->RotateDegrees = 180;
                        break;
                    case SDLK_ESCAPE:
                        Game::isRunning = false;
                        break;
                    default:
                        break;
                }
            }

            if(Game::event.type == SDL_KEYUP)
            {
                // cout << "Hey\n";
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_w:
                    case SDLK_UP:
                        transform->velocity.y = 0;
                        sprite->Play("Idle_U");
                        // sprite->spriteFlip = SDL_FLIP_NONE;
                        break;

                    case SDLK_a:
                    case SDLK_LEFT:
                        transform->velocity.x = 0;
                        sprite->Play("Idle_L");
                        sprite->spriteFlip = SDL_FLIP_NONE;
                        break;

                    case SDLK_d:
                    case SDLK_RIGHT:
                        transform->velocity.x = 0;
                        sprite->Play("Idle_R");
                        break;

                    case SDLK_s:
                    case SDLK_DOWN:
                        transform->velocity.y = 0;
                        sprite->Play("Idle_D");
                        break;

                    default:
                        break;
                }
            }
        }
};

#endif