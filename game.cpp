# pragma once
#include "MazeGeneration_DFS/Kruskal_Maze.cpp"
#include "game.hpp"
#include "TextureManager.hpp"
#include "Map.cpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Vector2D.cpp"
#include "Collision.cpp"
#include "MazeGeneration_DFS/MazeGeneration.cpp"
#include "ECS/EntityComponentSystem.cpp"
#include "Constants.hpp"

// GameObject* player = NULL;
// GameObject* enemy = NULL;

// Map* backgroundMap = NULL;   


MazeGenerator* Maze;

SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

bool Game::isRunning = false;
int Game::RowsToSkip = ROWS_TO_SKIP;
string Game::Color = BACKGROUND_COLOR;
int mapScale    = OVERALL_SCALE;
int windowScale = WINDOW_SCALE;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());



enum groupLabels : size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

Game::Game(){}

Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    
    int flag = SDL_WINDOW_SHOWN;
    if(fullscreen)flag = SDL_WINDOW_FULLSCREEN;

    if( SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        Game::isRunning = false;
        return;
    }
    else{
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flag);
        if( window == NULL){
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            Game::isRunning = false;
            return;
        }
        SDL_SetWindowResizable(window, SDL_TRUE);
        
        if( window == NULL)
        {printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        Game::isRunning = false;
        return;}
        
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer == NULL){
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            Game::isRunning = false;  
            return;
        }
        else{
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        // backgroundMap = new Map();
        Maze = new MazeGenerator(54);

        Map::LoadMap("Kruskal.txt", MAZE_ROWS, MAZE_COLUMNS);

        player.addComponent<TransformComponent>(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, DEFAULT_IMAGE_SIZE,
                                                 DEFAULT_IMAGE_SIZE, mapScale);
        player.addComponent<SpriteComponent>("assets/player.png", ANIMATION);
        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("Player");
        player.addGroup(groupPlayers);
        
    }
    Game::isRunning = true;
    return;
}

void Game::handleEvents(){
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            Game::isRunning = false;
            break;

        default:
            break;
    }
}

int collision_count = 0;

void Game::update(){
    
    manager.refresh();
    manager.update();

    camera.x = player.getComponent<TransformComponent>().position.x - SCREEN_WIDTH/2;
    camera.y = player.getComponent<TransformComponent>().position.y - SCREEN_HEIGHT/2;
    //cout<<"Player X: "<<player.getComponent<TransformComponent>().position.x<<"Player Y: "<<player.getComponent<TransformComponent>().position.y<<"\n";

    camera.x = max(camera.x,0);
    camera.y = max(camera.y,0);
    camera.x = min(camera.x, camera.w * ( mapScale / windowScale - 1 ) );
    camera.y = min(camera.y, camera.h * ( mapScale / windowScale - 1 ) );

    // Vector2D pVel = player.getComponent<TransformComponent>().velocity;
    // int pSpeed    = player.getComponent<TransformComponent>().speed;  

    // for(auto t: tiles)
    // {
    //     t->getComponent<TileComponent>().tileRect.x += -(pVel.x * pSpeed);
    //     t->getComponent<TileComponent>().tileRect.y += -(pVel.y * pSpeed);
    // }

    for(auto cc: colliders)
    {
        // if(*cc == player.getComponent<ColliderComponent>())continue;
        if(!Collision::EqualColliderComponent(player.getComponent<ColliderComponent>(), *cc))
        {
            if(Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
            {
                player.getComponent<TransformComponent>().velocity * -1;
                // player.getComponent<TransformComponent>().scale = 1;
                //cout << "COLLISION " <<  collision_count++ << "\n\n"; //HERE
            }
        }
    }

    // if( Collision::AABB(player.getComponent<ColliderComponent>().collider, 
    //                     wall.getComponent<ColliderComponent>().collider ) )
    // {
    //     player.getComponent<TransformComponent>().velocity * -1;
    //     // player.getComponent<TransformComponent>().scale = player.getComponent<TransformComponent>().scale/2;
    //     player.getComponent<TransformComponent>().scale = 1;
    //     cout << "COLLISION " <<  collision_count++ << "\n";
    // }

    // player.getComponent<TransformComponent>().position.Add(Vector2D(2,0));
    
    // if(player.getComponent<TransformComponent>().position.x > 100){
    //     player.getComponent<SpriteComponent>().setTex("assets/enemy.png");
    // }
    
    // if(player.getComponent<TransformComponent>().position.x > 200){
    //     player.getComponent<SpriteComponent>().setTex("assets/player.png");
    // }

}




void Game::render(){
    SDL_RenderClear(renderer);    
    // backgroundMap->DrawMap();
    // manager.draw();
    for(auto& t : tiles)
    {
        t->draw();
    }
    for(auto& p : players)
    {
        p->draw();
    }
    for(auto& e : enemies)
    {
        e->draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Ended\n";
}


void Game::AddTile(int id, int row, int col)
{
    if(id == -1)
    {
        auto& tile(manager.addEntity());
        tile.addComponent<TileComponent>(row, col, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, id, mapScale);
        // tile.addComponent<ColliderComponent>("Tiles");
        tile.addGroup(groupMap);
        // cout << id << "\n";
    }
    else
    {
        
        if(id%2 == 1)
        {
            auto& tile1(manager.addEntity());
            tile1.addComponent<TileComponent>(row, col + DEFAULT_IMAGE_SIZE - ROWS_TO_SKIP_PYTHON, ROWS_TO_SKIP_PYTHON, DEFAULT_IMAGE_SIZE, 0, DEFAULT_IMAGE_SIZE - ROWS_TO_SKIP_PYTHON, id, mapScale); //    |
            tile1.addComponent<ColliderComponent>("Tiles1");
            tile1.addGroup(groupMap);
        }

        if(id%4 >= 2)
        {
            auto& tile2(manager.addEntity());
            tile2.addComponent<TileComponent>(row + DEFAULT_IMAGE_SIZE - ROWS_TO_SKIP_PYTHON, col, DEFAULT_IMAGE_SIZE, ROWS_TO_SKIP_PYTHON, DEFAULT_IMAGE_SIZE - ROWS_TO_SKIP_PYTHON, 0, id, mapScale);//    __
            tile2.addComponent<ColliderComponent>("Tiles2");
            tile2.addGroup(groupMap);
        }

        if(id%16 >= 8)
        {
            auto& tile3(manager.addEntity());
            tile3.addComponent<TileComponent>(row, col, DEFAULT_IMAGE_SIZE, ROWS_TO_SKIP_PYTHON, 0, 0, id, mapScale); // |
            tile3.addComponent<ColliderComponent>("Tiles3");
            tile3.addGroup(groupMap);
        }

        if(id%8 >= 4)
        {
            auto& tile4(manager.addEntity());                                                              // __
            tile4.addComponent<TileComponent>(row, col, ROWS_TO_SKIP_PYTHON, DEFAULT_IMAGE_SIZE, 0, 0, id, mapScale);// 
            tile4.addComponent<ColliderComponent>("Tiles4");
            tile4.addGroup(groupMap);
        }
    }
    
}
