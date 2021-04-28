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
        SDL_Texture *texture;
        Vector2D position;

        int tileId;
        
        string temp_path = "";
        string color = "assets/GenerateTiles/" + Game::Color;

        TileComponent() = default;

        TileComponent(int x, int y, int w, int h, int id, int scaleBackground)
        {
            tileRect = {
                .x = y*scaleBackground,
                .y = x*scaleBackground,
                .w = w*scaleBackground,
                .h = h*scaleBackground,
            };

//             if(x == 0 && y == 0)
//             {
//                 cout << w << " " << h << " " <<  scaleBackground << endl;
//             }
            
            tileId = id;
            position.x = tileRect.x;
            position.y = tileRect.y;

            temp_path = color + "_" + to_string(id) + ".png";
            texture = TextureManager::LoadTexture(temp_path.c_str());
        }


        void update() override
        {
            tileRect.x = position.x - Game::camera.x;
            tileRect.y = position.y - Game::camera.y;
        }

        void draw() override
        {   
            TextureManager::Draw(texture, tileRect);
        }


};

#endif
