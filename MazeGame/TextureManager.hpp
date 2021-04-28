// #pragma once

#include "game.hpp"

#ifndef TextureManager_H
#define TextureManager_H

class TextureManager{
    public:
        static SDL_Texture* LoadTexture(const char* fileName);
        static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dst, SDL_RendererFlip flip, int RotateDegrees);
        static void Draw(SDL_Texture* tex, SDL_Rect dst);
};

#endif