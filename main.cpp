#include "game.hpp"
#include "TextureManager.hpp"
#include "game.cpp"
// #include "GameObject.hpp"
// #include "GameObject.cpp"
#include "TextureManager.cpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Constants.hpp"

using namespace std;

Game* game = NULL;


int main(int argc, char* argv[]){
     
    game = new Game();

    const int FPS = FRAMES_PER_SECOND;
    const int FrameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;
    
    game -> init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, false);

    while(game -> running()){
        

        SDL_PollEvent(&Game::event);
        if(Game::event.type == SDL_KEYDOWN){
            if(Game::event.key.keysym.sym == SDLK_p){
                Game::paused = !Game::paused;
            }

            else if(Game::event.key.keysym.sym == SDLK_ESCAPE){
                Game::isRunning = false;
            }

        }

        else if(Game::event.type == SDL_QUIT){
            Game::isRunning = false;
        }
        
        if(!Game::paused)
        {
            frameStart = SDL_GetTicks();

            game -> handleEvents();
            game -> update();
            game -> render();

            frameTime = SDL_GetTicks() - frameStart;
            
            if(FrameDelay > frameTime){
                SDL_Delay(FrameDelay - frameTime);
            }

        }

    }
    game -> clean();
    return 0;
}
