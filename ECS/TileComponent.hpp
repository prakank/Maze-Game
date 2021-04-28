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
        string color = "assets/GenerateTiles/Black";

        TileComponent() = default;

        TileComponent(int x, int y, int w, int h, int id, int scaleBackground)
        {
            tileRect = {
                .x = y*scaleBackground,
                .y = x*scaleBackground,
                .w = w*scaleBackground,
                .h = h*scaleBackground,
            };
            
            tileId = id;
            position.x = tileRect.x;
            position.y = tileRect.y;

            temp_path = color + "_" + to_string(id) + ".png";
            texture = TextureManager::LoadTexture(temp_path.c_str());

            // if(tileRect.x == 0)
            // cout << tileRect.x << " " << tileRect.y << " " <<  id << " " << temp_path << "\n";
            
            // cout << temp_path << endl;
            // strcpy(path, temp_path.c_str());
            // path = temp_path;

            // switch(tileId)
            // {
            //     case 0:
            //         path = "assets/water.png";
            //         break;
            //     case 1:
            //         path = "assets/dirt.png";
            //         break;
            //     case 2:
            //         path = "assets/grass.png";
            //         break;
            //     default:
            //         break;                
            // }

        }

        // void init() override
        // {   
        //     entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
        //     transform = &entity->getComponent<TransformComponent>();
        //     entity->addComponent<SpriteComponent>(temp_path.c_str());
        //     sprite = &entity->getComponent<SpriteComponent>();
        // }

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