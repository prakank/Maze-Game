#include "ECS/EntityComponentSystem.hpp"
#include "ECS/TransformComponent.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_mixer.h>
#include "game.hpp"

Mix_Chunk *menuButton;
Mix_Chunk *pacmanCoinMusic;
Mix_Music *backgroundMusic;

void menu_button_sound()
{
    Mix_PlayChannel(-1,menuButton,0);
}

void pacman_coin()
{
    Mix_PlayChannel(-1,pacmanCoinMusic,0);
}

bool renderMenu(string theme)
{
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);
    pacmanCoinMusic = Mix_LoadWAV("assets/sounds/coin_collect.mp3");
    menuButton = Mix_LoadWAV("assets/sounds/button_hover.ogg");
    backgroundMusic = Mix_LoadMUS("assets/sounds/pacman_beginning.wav");
    
    Mix_PlayMusic(backgroundMusic,-1);
    
    if(theme == "pacman")
    {
        int option = 0; // Start
        int total_options = 2;
        int shift  = 10;

        SDL_Rect src_back    = {0,0,SCREEN_WIDTH, SCREEN_HEIGHT};
        SDL_Rect dst_back    = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        SDL_Rect src_heading = {0,0,408, 92};
        SDL_Rect dst_heading = {(SCREEN_WIDTH/2) - 204,(SCREEN_HEIGHT/2)-146,408,92};
        SDL_Rect src_start   = {0,0,137, 37};
        SDL_Rect dst_start   = {(SCREEN_WIDTH/2) - (137*3)/4, (SCREEN_HEIGHT/2) -75 + 46 + 2*shift, 137 + 137/2, 37*2};
        SDL_Rect src_exit    = {0,0,137, 37};
        SDL_Rect dst_exit    = {(SCREEN_WIDTH/2) - (137*3)/4, (SCREEN_HEIGHT/2) -75 + 46 + 37*2 + 3*shift, 137 + 137/2, 37*2};

        SDL_Texture* background = TextureManager::LoadTexture("assets/light_background.jpg");
        SDL_Texture* heading    = TextureManager::LoadTexture("assets/pacman_heading.png");
        SDL_Texture* start      = TextureManager::LoadTexture("assets/start-1.png");
        SDL_Texture* exit       = TextureManager::LoadTexture("assets/exit-2.png");
        TextureManager::Draw(background, src_back, dst_back);
        TextureManager::Draw(heading, src_heading, dst_heading);
        TextureManager::Draw(start, src_start, dst_start);
        TextureManager::Draw(exit, src_exit, dst_exit);
        
        SDL_RenderPresent(Game::renderer);
        int i=0;

        while(Game::showMenu)
        {
            SDL_PollEvent(&Game::event);

            switch(Game::event.type)
            {
                case SDL_QUIT:
                    Game::isRunning = false;
                    break;

                case SDL_KEYDOWN:
                    switch (Game::event.key.keysym.sym) 
                    {
                        case SDLK_UP:                            
                            option--;
                            option = (option + total_options)%total_options;
                            if(option == 0)
                            {
                                start      = TextureManager::LoadTexture("assets/start-1.png");
                                exit       = TextureManager::LoadTexture("assets/exit-2.png");
                            }
                            else
                            {
                                start      = TextureManager::LoadTexture("assets/start-2.png");
                                exit       = TextureManager::LoadTexture("assets/exit-1.png");
                            }                
                            TextureManager::Draw(start, src_start, dst_start);
                            TextureManager::Draw(exit, src_exit, dst_exit);
                            SDL_RenderPresent(Game::renderer);
                            Mix_PlayChannel(-1,menuButton,0);
                            menu_button_sound();
                            SDL_Delay(150);
                            break;
                            
                        case SDLK_DOWN:
                            option++;
                            option = (option + total_options)%total_options;
                            if(option == 0)
                            {
                                start      = TextureManager::LoadTexture("assets/start-1.png");
                                exit       = TextureManager::LoadTexture("assets/exit-2.png");
                            }
                            else
                            {
                                start      = TextureManager::LoadTexture("assets/start-2.png");
                                exit       = TextureManager::LoadTexture("assets/exit-1.png");
                            }                
                            TextureManager::Draw(start, src_start, dst_start);
                            TextureManager::Draw(exit, src_exit, dst_exit);
                            SDL_RenderPresent(Game::renderer);
                            Mix_PlayChannel(-1,menuButton,0);
                            menu_button_sound();
                            SDL_Delay(150);
                            break;

                        case 13:
                            Mix_PauseMusic();
                            Game::showMenu = false;
                            if(option == 1)
                            {
                                Game::isRunning = false;
                                return false;
                            }
                            return true;                            
                            break;

                        case SDLK_ESCAPE:
                            Game::isRunning = false;
                            Game::showMenu = false;
                            break;

                        default:
                            //cout << "Invalid Key\n";
                            break;
                    }
                    //cout << i++ << ".) " << option << "\n";
                    
                    break;

                default:
                    break;
            }
        }
    }
}


// Transparent Tile, Background (LunaPic)
// Player and Enemy -< Stats Component
// Display at the bottom