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
