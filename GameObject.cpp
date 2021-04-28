#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y){
    // renderer = ren;
    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
}

void GameObject::Update(){
    
    xpos++;
    ypos++;
    
    srcRect = {
        .x = 0,
        .y = 0,
        .w = 64,
        .h = 64,        
    };
    
    dstRect = {
        .x = xpos,
        .y = ypos,
        .w = srcRect.w,
        .h = srcRect.h,
    };  
}

void GameObject::Render(){
    SDL_RenderCopy(Game::renderer, objTexture, NULL, &dstRect);
}