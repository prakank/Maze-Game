// #include "ECS/EntityComponentSystem.hpp"
// #include "ECS/TransformComponent.hpp"
// #include "TextureManager.hpp"
// #include "Player.hpp"
// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
// #include <SDL2/SDL_mixer.h>
// #include <SDL2/SDL_ttf.h>
// #include "game.hpp"

// loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont)
// {
//     SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
//     if (textSurface == NULL) 
//     {
//         printf("Unable to render text surface! SDL_ttf Error: %s\n",
//         TTF_GetError());
//     }
//     else
//     {
//         SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, textSurface);
//     }
//     if (tex == NULL) 
//     {
//         printf("Unable to create texture from rendered text! SDL Error: %s\n",
//         SDL_GetError());
//     } else {
//       // Get image dimensions
//       mWidth = textSurface->w;
//       mHeight = textSurface->h;
//     }
// }
