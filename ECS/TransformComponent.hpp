#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include "Components.hpp"
#include "../Vector2D.hpp"
#include "../game.hpp"

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
            position.x = 400; // Starting with centre of the screen
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
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;

            position.x = max(position.x,0.0f);
            position.y = max(position.y,0.0f);

            position.x = min(position.x, static_cast<float>(Game::camera.x + Game::camera.w - width *scale  ) );
            position.y = min(position.y, static_cast<float>(Game::camera.y + Game::camera.h - height*scale ) );
        }

};

#endif