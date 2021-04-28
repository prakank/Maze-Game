#include "game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "game.cpp"
#include "GameObject.cpp"
#include "TextureManager.cpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"

using namespace std;

Game* game = NULL;


int main(int argc, char* argv[]){
     
    game = new Game();

    const int FPS = 60;
    const int FrameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;
    
    game -> init("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

    while(game -> running()){

        frameStart = SDL_GetTicks();

        game -> handleEvents();
        game -> update();
        game -> render();

        frameTime = SDL_GetTicks() - frameStart;
        
        if(FrameDelay > frameTime){
            SDL_Delay(FrameDelay - frameTime);
        }

    }
    game -> clean();
    return 0;
}
