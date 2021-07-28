#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "ECS/ColliderComponent.hpp"
#include <SDL2/SDL.h>

class ColliderComponent;

class Collision{

    public:
        
        // Access Aligned Bounding Box tyoe Collision
        static bool AABB(const SDL_Rect& a, const SDL_Rect& b);
        static bool AABB(const ColliderComponent& a, const ColliderComponent& b);
        static bool EqualColliderComponent(const ColliderComponent& a, const ColliderComponent& b);

};

#endif