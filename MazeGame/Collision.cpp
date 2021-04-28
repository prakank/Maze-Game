#include "Collision.hpp"

bool Collision::AABB(const SDL_Rect& a, const SDL_Rect& b)
{
    if(a.x + a.w >= b.x && 
       b.x + b.w >= a.x && 
       a.y + a.h >= b.y && 
       b.y + b.h >= a.y )return true;
    return false;
}

bool Collision::AABB(const ColliderComponent& a, const ColliderComponent& b)
{
    if( AABB(a.collider, b.collider ) )
    {
        cout << a.tag << " hit: " << b.tag << endl;
        return true;
    }
    return false;
}

bool Collision::EqualColliderComponent(const ColliderComponent& a, const ColliderComponent& b)
{
    if(a.collider.x == b.collider.x &&
        a.collider.y == b.collider.y &&
        a.collider.w == b.collider.w &&
        a.collider.h == b.collider.h &&
        a.tag == b.tag        
    )return true;
    return false;
}