#ifndef TRANSFORM_COMPONENT
#define TRANSFORM_COMPONENT

#include "Components.hpp"
#include "../Vector2D.hpp"
#include "../game.hpp"
#include "../Constants.hpp"
// #include "SpriteComponent.hpp"

class TransformComponent : public Component{

    public:

        Vector2D position;
        Vector2D velocity;
        int speed = PLAYER_SPEED;

        int height = 32;
        int width  = 32; 
        float scale = 1;

        int dstWidth;
        int dstHeight;

        TransformComponent()
        {
            position.Zero();
        }

        TransformComponent(float s)
        {
            position.x = SCREEN_WIDTH/2; // Starting with centre of the screen
            position.y = SCREEN_HEIGHT/2;
            scale = s;
        }

        TransformComponent(float x, float y)
        {
            position.x = y;
            position.y = x;
        }
        
        TransformComponent(float x, float y, int w, int h, float s)
        {
            position.x = x;
            position.y = y;
            width = w;
            height = h;
            scale = s;
        }

        void init() override
        {
            velocity.Zero();
            dstWidth = (width - ROWS_TO_SKIP) * scale;
            dstHeight = (height - ROWS_TO_SKIP) * scale;
        }

        void update() override
        {   
            position.x += velocity.x * speed;
            position.y += velocity.y * speed;

            position.x = max(position.x,(ROWS_TO_SKIP/2) * scale);
            position.y = max(position.y,(ROWS_TO_SKIP/2) * scale);

            // player_dstRect = entity->getComponent<SpriteComponent>().dstRect;

            position.x = min(position.x, static_cast<float>(Game::camera.x + Game::camera.w - dstWidth  - (ROWS_TO_SKIP/2) * scale ) );
            position.y = min(position.y, static_cast<float>(Game::camera.y + Game::camera.h - dstHeight - (ROWS_TO_SKIP/2) * scale ) );
        }

};

#endif