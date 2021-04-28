#include "game.hpp"
#include "TextureManager.hpp"
#include "Map.cpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"
#include "Vector2D.cpp"
#include "Collision.cpp"
#include "MazeGeneration_DFS/MazeGeneration.cpp"
#include "ECS/EntityComponentSystem.cpp"

// GameObject* player = NULL;
// GameObject* enemy = NULL;

// Map* backgroundMap = NULL;

MazeGeneration* MazeGenerator;

SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;

SDL_Rect Game::camera = {0, 0, 800, 640};

bool Game::isRunning = false;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity());
auto& wall(manager.addEntity());

int scaleBackground = 4;

enum groupLabels : size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

// auto& tile0(manager.addEntity());
// auto& tile1(manager.addEntity());
// auto& tile2(manager.addEntity());


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
        MazeGenerator = new MazeGeneration();
        MazeGenerator -> MazeGenerator();

        Map::LoadMap("assets/Maze.txt", 20, 25);

        player.addComponent<TransformComponent>(scaleBackground);
        player.addComponent<SpriteComponent>("assets/player.png", false);
        player.addComponent<KeyboardController>();
        player.addComponent<ColliderComponent>("Player");
        player.addGroup(groupPlayers);

        // wall.addComponent<TransformComponent>(300.0f,300.0f, 300, 20, 1);
        // wall.addComponent<SpriteComponent>("assets/dirt.png");
        // wall.addComponent<ColliderComponent>("wall");
        // wall.addGroup(groupMap);
        
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

    camera.x = player.getComponent<TransformComponent>().position.x - 400;
    camera.y = player.getComponent<TransformComponent>().position.y - 320;

    camera.x = max(camera.x,0);
    camera.y = max(camera.y,0);
    camera.x = min(camera.x, camera.w * ( scaleBackground - 1 ) );
    camera.y = min(camera.y, camera.h * ( scaleBackground - 1 ) );

    // Vector2D pVel = player.getComponent<TransformComponent>().velocity;
    // int pSpeed    = player.getComponent<TransformComponent>().speed;  

    // for(auto t: tiles)
    // {
    //     t->getComponent<TileComponent>().tileRect.x += -(pVel.x * pSpeed);
    //     t->getComponent<TileComponent>().tileRect.y += -(pVel.y * pSpeed);
    // }

    // for(auto cc: colliders)
    // {
    //     // if(*cc == player.getComponent<ColliderComponent>())continue;
    //     if(!Collision::EqualColliderComponent(player.getComponent<ColliderComponent>(), *cc))
    //     if(Collision::AABB(player.getComponent<ColliderComponent>(), *cc))
    //     {
    //         player.getComponent<TransformComponent>().velocity * -1;
    //         // player.getComponent<TransformComponent>().scale = 1;
    //         cout << "COLLISION " <<  collision_count++ << "\n";
    //     }
    // }

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


void Game::AddTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x, y, 32, 32, id, scaleBackground);
    // tile.addComponent<ColliderComponent>("Tiles");
    tile.addGroup(groupMap);
    // cout << id << "\n";
}
