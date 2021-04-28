#ifndef SPRITE_COMPONENT
#define SPRITE_COMPONENT

#include "Components.hpp"
#include <SDL2/SDL.h>
#include "../TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class SpriteComponent : public Component
{
    private:
        TransformComponent *transform;
        SDL_Texture* texture = NULL;
        SDL_Rect srcRect, dstRect;
        bool animate = false;
        int frames = 4;
        int speed = 100;

    public:        

        int animIndex = 0;

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

            Animation idle = Animation(0, 3, 100);
            Animation move = Animation(1, 8, 200);

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

            dstRect.x = static_cast<int>(transform->position.x);
            dstRect.y = static_cast<int>(transform->position.y);
            dstRect.w = transform->width * transform->scale;
            dstRect.h = transform->height * transform->scale;
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