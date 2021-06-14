# pragma once
#include "Player.hpp"
#include "Enemy.hpp"
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




SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;
MazeGenerator* Game::Maze;

SDL_Rect Game::camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

bool Game::isRunning = false;
int Game::RowsToSkip = ROWS_TO_SKIP;
string Game::Color = BACKGROUND_COLOR;
float mapScale    = OVERALL_SCALE;
float windowScale = WINDOW_SCALE;

std::vector<ColliderComponent*> Game::colliders;

Manager manager;
auto& player(manager.addEntity<Player>());
auto& enemy(manager.addEntity<Enemy>());




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
        Game::Maze = new MazeGenerator(54);

        Map::LoadMap("Kruskal.txt", MAZE_ROWS, MAZE_COLUMNS);

        //if(player.manager == manager)cout<<"player has component\n";
        player.init();
        player.addGroup(groupPlayers);

        enemy.init();
        enemy.addGroup(groupEnemies);

        
        
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

    // Vector2D pVel = player.getComponent<TransformComponent>().velocity;
    // int pSpeed    = player.getComponent<TransformComponent>().speed;  

    // for(auto t: tiles)
    // {
    //     t->getComponent<TileComponent>().tileRect.x += -(pVel.x * pSpeed);
    //     t->getComponent<TileComponent>().tileRect.y += -(pVel.y * pSpeed);
    // }

    for(auto cc: colliders)
    {
        if(!Collision::EqualColliderComponent(player.getComponent<ColliderComponent>(), *cc))
        {
            if(Collision::AABB(player.getComponent<ColliderComponent>(), *cc) && cc->entity->hasComponent<TileComponent>())
            {
                auto& rect = cc->entity->getComponent<ColliderComponent>().collider;
                auto& rect_p = player.getComponent<ColliderComponent>().collider;
                auto& pos_p = player.getComponent<TransformComponent>().position;
                auto& vel = player.getComponent<TransformComponent>().velocity;

                if(true){
                    if(rect.w<rect.h){
                        if(rect_p.x + rect_p.w/2 < rect.x){
                            pos_p.x = rect.x - rect_p.w - 2 - 8;
                        }

                        else if(rect_p.x + rect_p.w/2 >= rect.x){
                            pos_p.x = rect.x + rect.w + 2 - 8;
                        }
                    }
                    else{
                        if(rect_p.y + rect_p.h/2 < rect.y){
                            pos_p.y = rect.y - rect_p.h - 2 - 10;
                        }
                        else if(rect_p.y + rect_p.h/2 >= rect.y){
                            pos_p.y = rect.y + rect.h + 2 - 10;
                        }
                    }
                }
                
                
            }
        }

        if(!Collision::EqualColliderComponent(enemy.getComponent<ColliderComponent>(), *cc))
        {
            if(Collision::AABB(enemy.getComponent<ColliderComponent>(), *cc) && cc->entity->hasComponent<TileComponent>())
            {
                auto& rect = cc->entity->getComponent<ColliderComponent>().collider;
                auto& rect_p = enemy.getComponent<ColliderComponent>().collider;
                auto& pos_p =enemy.getComponent<TransformComponent>().position;
                auto& vel = enemy.getComponent<TransformComponent>().velocity;

                if(true){
                    if(rect.w<rect.h){
                        if(rect_p.x + rect_p.w/2 < rect.x){
                            pos_p.x = rect.x - rect_p.w - 2 - 8;
                        }

                        else if(rect_p.x + rect_p.w/2 >= rect.x){
                            pos_p.x = rect.x + rect.w + 2 - 8;
                        }
                    }
                    else{
                        if(rect_p.y + rect_p.h/2 < rect.y){
                            pos_p.y = rect.y - rect_p.h - 2 - 10;
                        }
                        else if(rect_p.y + rect_p.h/2 >= rect.y){
                            pos_p.y = rect.y + rect.h + 2 - 10;
                        }
                    }
                }

                Game::enemyChangeDirection(enemy);
                
                
            }
        }
    }



}




void Game::render(){

    SDL_RenderClear(renderer);
    // backgroundMap->DrawMap();
    //manager.draw();
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

//////////////////////
//////////////////////
//////////////////////
//////////////////////
// uncomment below to view collider boxes
//
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 120);
    for(auto cc:colliders){
        SDL_RenderDrawRect(renderer, &cc->collider);
    }

    
    

//////////////////////
//////////////////////
//////////////////////

    SDL_RenderPresent(renderer);
}


void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Ended\n";
}

//other functions


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

vector<int> Game::checkTile(Entity& e){
    auto collider = e.getComponent<ColliderComponent>().collider;
    int x = collider.x + collider.w/2;
    int y = collider.y + collider.h/2;
    vector<int> v;
    v.pb(y/TILE_SIZE);
    v.pb(x/TILE_SIZE);
    return v;
}

/*static void Game::enemyAI(Entity& player, Entity& enemy){
    vector<int> tile_p = checkTile(player);
    vector<int> tile_en = checkTile(enemy);


}*/

void Game::enemyChangeDirection(Entity& enemy){

    //used rectangle collider_transform diff
    vector<int> tile = Game::checkTile(enemy);
    auto& pos = enemy.getComponent<TransformComponent>().position;
    auto& ai = enemy.getComponent<AIController>();
    vector<int> dir;
    for(int i = 0;i<4;i++)
    {
        if(Game::Maze->nodes[tile[0]][tile[1]]->neighbours[i]) dir.pb(i);
    }

    cout<<"Info:\n tile: ("<<tile[0]<<", "<<tile[1]<<")\ndir: "<<"\n";
    cout<<"dirs: \n";
    for(int i = 0;i < dir.size();i++){
       cout<<dir[i]<<"\n";
    }
    cout<<"player: X = "<<pos.x<<", Y = "<<pos.y<<"\n";

    srand(time(0));
    int seed = rand();
    int fin_dir = dir[(seed % dir.size() + dir.size()) % dir.size()];
    ai.MovementDirection = fin_dir;

}

/*bool Game::checkEnemyBoundingBox(Entity& enemy){

}*/


