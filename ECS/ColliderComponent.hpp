#ifndef COLLIDER_COMPONENT_HPP
#define COLLIDER_COMPONENT_HPP

#include <string>
#include "SDL.h"
// #include "EntityComponentSystem.hpp"
#include "Components.hpp"


class ColliderComponent : public Component 
{
    public:
        SDL_Rect collider;
        std::string tag;

        TransformComponent* transform;

        ColliderComponent(std::string t)
        {   
            tag = t;
            // cout << tag << endl;
        }

        void init() override
        {
            if( !entity->hasComponent<TransformComponent>() )
            {
                entity->addComponent<TransformComponent>();
            }
            transform = &entity->getComponent<TransformComponent>();
            // Check if same colliderComponent gets multiple calls to init        

            Game::colliders.push_back(this);
        }

        void update() override
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = static_cast<int>(transform->width * transform->scale);
            collider.h = static_cast<int>(transform->height * transform->scale);
        }
};

#endif