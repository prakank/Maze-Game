#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include "Components.hpp"
#include "../Vector2D.hpp"

class TransformComponent : public Component{

    public:

        Vector2D position;
        Vector2D velocity;
        int speed = 5;

        int height = 32;
        int width = 32;
        float scale = 1;

        TransformComponent()
        {
            position.Zero();
        }

        TransformComponent(float s)
        {
            position.x = 400;
            position.y = 320;
            scale = s;
        }

        TransformComponent(float x, float y)
        {
            position.x = y;
            position.y = x;
        }
        
        TransformComponent(float x, float y, int w, int h, float s)
        {
            position.x = y;
            position.y = x;
            width = w;
            height = h;
            scale = s;
        }

        void init() override
        {
            velocity.Zero();
        }

        void update() override
        {   
            // position.x += velocity.x * speed;
            // position.y += velocity.y * speed;
        }

};

#endif