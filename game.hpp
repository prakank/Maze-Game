// #pragma once

// Alternative for #pragma once
#ifndef GAME_HPP  
#define GAME_HPP


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <bits/stdc++.h>
#include <vector>

class ColliderComponent;

using namespace std;

class Game{

    public:
        Game();
        ~Game();
        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        void handleEvents();
        void update();
        void render();
        void clean();
        bool running(){return isRunning;}
                
        static SDL_Renderer* renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;
        static void AddTile(int id, int x, int y);
        
        static SDL_Rect camera;
        static bool isRunning;
        static int RowsToSkip;
        static string Color;

    private:
        
        int cnt = 0;
        SDL_Window* window = NULL;
    
};

#endif