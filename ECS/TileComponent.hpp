#ifndef TILE_COMPONENT_HPP
#define TILE_COMPONENT_HPP

#include "EntityComponentSystem.hpp"
#include "TransformComponent.hpp"
#include "../TextureManager.hpp"
#include <SDL2/SDL.h>
#include "../game.hpp"

class TileComponent : public Component 
{
    public:

        SDL_Rect tileRect;  // Acts as the dst Rect
        SDL_Rect srcRect;
        SDL_Texture *texture;
        Vector2D position;

        int tileId;
        
        string temp_path = "";
        string color = "assets/GenerateTiles/" + Game::Color;

        // TransformComponent* transform;

        TileComponent() = default;

        TileComponent(int y, int x, int w, int h, int srcY, int srcX, int id, int scaleBackground)
        {
            if(id == -1)
            {
                tileRect = {
                    .x   = x,
                    .y   = y,
                    .w   = w,
                    .h   = h,
                };

            }

            else
            {
                tileRect = {
                    .x = x*scaleBackground,
                    .y = y*scaleBackground,
                    .w = w*scaleBackground,
                    .h = h*scaleBackground,
                };
            }


            srcRect = {
                .x  = srcX,
                .y  = srcY,
                .w  = w,
                .h  = h, 
            };

            // &entity->addComponent<TransformComponent>(tileRect.x, tileRect.y, w, h, scaleBackground);

            // cout << "TarX: " << x << ", TarY: " << y << ", SrcX: " << srcX << ", SrcY: " << srcY << ", Tile: " << id << endl;
            // cout << "Width: " << w << ", Height: " << h << endl;

            tileId = id;
            position.x = tileRect.x;
            position.y = tileRect.y;
            
            if(tileId == -1) temp_path = color + "Background.png";
            else if(tileId == -2)temp_path = color + "Background_Score.png";
            else temp_path = color +  "2_" + to_string(id) + ".png";            
            
            texture = TextureManager::LoadTexture(temp_path.c_str());
        }


        void update() override
        {
            tileRect.x = position.x - Game::camera.x;
            tileRect.y = position.y - Game::camera.y;
        }

        void draw() override
        {   
            TextureManager::Draw(texture, srcRect, tileRect);
        }


};

#endif
