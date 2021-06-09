#include "Collision.hpp"

bool Collision::AABB(const SDL_Rect& a, const SDL_Rect& b)
{
    if(a.x + a.w >= b.x - 1 && 
       b.x + b.w >= a.x - 1 && 
       a.y + a.h >= b.y - 1 && 
       b.y + b.h >= a.y - 1)return true;
    return false;
}

bool Collision::AABB(const ColliderComponent& a, const ColliderComponent& b)
{
    if( AABB(a.collider, b.collider ) )
    {
        cout << a.tag << " hit: " << b.tag << endl;
        // cout << "X: " << a.collider.x << ", " << b.collider.x << endl;
        // cout << "Y: " << a.collider.y << ", " << b.collider.y << endl;
        // cout << "Width: " << a.collider.w << ", " << b.collider.w << endl;
        // cout << "Height: " << a.collider.h << ", " << b.collider.h << endl << endl;
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