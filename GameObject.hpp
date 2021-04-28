// #pragma once

#include "TextureManager.hpp"

#ifndef GameObject_H
#define GameObject_H

class GameObject{
    public:
        GameObject(const char* texturesheet, int x, int y);
        ~GameObject();

        void Update();
        void Render();

    private:
        int xpos, ypos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, dstRect;
        // SDL_Renderer* renderer;
};

#endif