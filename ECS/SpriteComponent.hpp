#ifndef SPRITE_COMPONENT
#define SPRITE_COMPONENT

#include "Components.hpp"
#include <SDL2/SDL.h>
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include "../game.hpp"
#include "../Constants.hpp"
#include <map>

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture* texture = NULL;
        
        bool animate = false;
        int frames = 4;
        int speed = ANIMATION_SPEED;

    public:        

        int animIndex = 0;

        SDL_Rect srcRect, dstRect;

        std::map<const char*, Animation> animations;
        
        SDL_RendererFlip spriteFlip = SDL_FLIP_NONE; 
        int RotateDegrees = 0;

        SpriteComponent() = default;
        SpriteComponent(const char* path)
        {
            // texture = TextureManager::LoadTexture(path);
            setTex(path);
        }

        SpriteComponent(const char* path, bool isAnimated)
        {
            animate = isAnimated;

            Animation idle = Animation(0, FRAMES_FOR_IDLE,   ANIMATION_SPEED);
            Animation move = Animation(1, FRAMES_FOR_MOTION, ANIMATION_SPEED);

            animations.emplace("Idle", idle);
            animations.emplace("Move", move);

            Play("Idle");


            setTex(path);
        }

        ~SpriteComponent()
        {
            SDL_DestroyTexture(texture);
        }

        void setTex(const char* path){
            texture = TextureManager::LoadTexture(path);
        }

        void init() override
        {
            transform = &entity->getComponent<TransformComponent>();

            srcRect.x = srcRect.y = 0;
            srcRect.w = transform->width;
            srcRect.h = transform->height;
        }

        void update() override
        {   
            if(animate)
            {
                srcRect.x = srcRect.w * static_cast<int>( (SDL_GetTicks() / speed) % frames );
            }

            srcRect.y = animIndex * transform->height;

            dstRect.x = static_cast<int>(transform->position.x) - Game::camera.x;
            dstRect.y = static_cast<int>(transform->position.y) - Game::camera.y;
            dstRect.w = ( transform->width  - Game::RowsToSkip )* transform->scale;
            dstRect.h = ( transform->height - Game::RowsToSkip )* transform->scale;

            
            // cout << transform->width << " " << Game::RowsToSkip << " " << transform->scale << endl;
            // cout << dstRect.w << " " << dstRect.h << " " <<  transform->scale << "\n";
        }

        void draw() override
        {
            TextureManager::Draw(texture, srcRect, dstRect, spriteFlip, RotateDegrees);
        }

        void Play(const char* animName)
        {
            frames = animations[animName].frames;
            speed = animations[animName].speed;
            animIndex = animations[animName].index;
        }

};

#endif