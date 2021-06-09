#ifndef COLLIDER_COMPONENT_HPP
#define COLLIDER_COMPONENT_HPP

#include <string>
#include "SDL.h"
// #include "EntityComponentSystem.hpp"
#include "Components.hpp"
#include "TileComponent.hpp"


class ColliderComponent : public Component 
{
    public:
        SDL_Rect collider;
        std::string tag;

        TransformComponent* transform;
        TileComponent* tileComp;
        int ColliderWidth = 0;
        int ColliderHeight = 0;

        ColliderComponent(std::string t)
        {   
            tag = t;
            // cout << tag << endl;
        }

        void init() override
        {
            
        // ==========================================================================================================
        // ==========================================================================================================
        // ==========================================================================================================
        // ==========================================================================================================
        // ==========================================================================================================

            // BE CAREFUL
            // MIGHT CAUSE PROBLEMS IN FUTURE
            
        // ==========================================================================================================
        // ==========================================================================================================
        // ==========================================================================================================
        // ==========================================================================================================
        // ==========================================================================================================

            tileComp = &entity->getComponent<TileComponent>();
            if( !entity->hasComponent<TransformComponent>() )
            {
                entity->addComponent<TransformComponent>(tileComp->tileRect.x, tileComp->tileRect.y, 
                                                        tileComp->tileRect.w, tileComp->tileRect.h, 1);

                // ColliderWidth  =  tileComp->tileRect.w;
                // ColliderHeight =  tileComp->tileRect.h;
            }
            else
            {
                // ColliderWidth = transform->width;
                // ColliderHeight = transform->dstHeight;
            }
            transform = &entity->getComponent<TransformComponent>();
            // transform->dstWidth = tileComp->tileRect.w;
            // transform->dstHeight = tileComp->tileRect.w;
            // Check if same colliderComponent gets multiple calls to init        

            Game::colliders.push_back(this);
            // cout << "Working\n";
        }

        void update() override
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = static_cast<int>(transform->width * transform->scale);
            collider.h = static_cast<int>(transform->height * transform->scale);

            //hardcoding here
            if(!entity->hasComponent<TileComponent>())
            {
                collider.y = collider.y + 10;
                collider.h = collider.h - 10;
                collider.x = collider.x + 8;
                collider.w = collider.w - 16;
            }
            //collider.w = static_cast<int>(transform->dstWidth);
            //collider.h = static_cast<int>(transform->dstHeight);
        }
};

#endif