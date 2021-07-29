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
#include "menu.cpp"
#include "MazeGeneration_DFS/MazeGeneration.cpp"
#include "ECS/EntityComponentSystem.cpp"
#include "Constants.hpp"
#include "ECS/Animation.hpp"
#include<queue>

SDL_Renderer* Game::renderer = NULL;
SDL_Event Game::event;
MazeGenerator* Game::Maze;

SDL_Rect Game::camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

bool Game::paused = false;
Manager* Game::manager = new Manager();
bool Game::isRunning = false;
bool Game::showMenu = true;
int Game::RowsToSkip = ROWS_TO_SKIP;
string Game::Color = BACKGROUND_COLOR;
float mapScale    = OVERALL_SCALE;
float windowScale = WINDOW_SCALE;

std::vector<ColliderComponent*> Game::colliders;

//Manager manager;

auto& collectibles(Game::manager->getGroup(groupCollectibles));
auto& tiles(Game::manager->getGroup(groupMap));
auto& players(Game::manager->getGroup(groupPlayers));
auto& enemies(Game::manager->getGroup(groupEnemies));

Game::Game(){}

Game::~Game(){}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    
    int flag = SDL_WINDOW_SHOWN;
    if(fullscreen)flag = SDL_WINDOW_FULLSCREEN;
    bool assignMenu = true;

    if( SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        Game::isRunning = false;
        return;
    }
    else{
        window = SDL_CreateWindow(title, xpos, ypos, width, height+100, flag);
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
        // ===============================================================================
        // Main Menu
        assignMenu = renderMenu("pacman");
        // ===============================================================================
        
        Game::Maze = new MazeGenerator(54);

        Map::LoadMap("Kruskal.txt", MAZE_ROWS, MAZE_COLUMNS);

        //if(player.manager == manager)cout<<"player has component\n";
        auto& player(Game::manager->addEntity<Player>());
        player.init();

        auto& enemy(Game::manager->addEntity<Enemy>());
        enemy.init();

        for(int i=0;i<MAZE_COLUMNS;i++)
        {
            for(int j=0;j<MAZE_ROWS;j++)
            {
                Game::addDragonBall(i,j,max((i+j)%7,1));
            }
        }
        Game::addDragonBall(1, MAZE_ROWS, -1);
    }
    Game::isRunning = assignMenu;
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
    
    Game::manager->refresh();
    Game::manager->update();

    // Vector2D pVel = player.getComponent<TransformComponent>().velocity;
    // int pSpeed    = player.getComponent<TransformComponent>().speed;  

    // for(auto t: tiles)
    // {
    //     t->getComponent<TileComponent>().tileRect.x += -(pVel.x * pSpeed);
    //     t->getComponent<TileComponent>().tileRect.y += -(pVel.y * pSpeed);
    // }

    auto it_player = players.begin();    

    while(it_player!=players.end())
    {
        auto player = players[it_player - players.begin()];
        auto it_collectibles = collectibles.begin();
        auto it_tiles = tiles.begin();
        
        while(it_collectibles != collectibles.end())
        {
            auto cc = collectibles[it_collectibles - collectibles.begin()];
            if(Collision::AABB(player->getComponent<ColliderComponent>(), cc->getComponent<ColliderComponent>()))
            {
                pacman_coin();
                collectibles.erase(it_collectibles);
                players[it_player - players.begin()]->getComponent<StatsComponent>().coinCount++;
                // players[it_player - players.begin()]->getComponent<Player>().score++;
            }
            else it_collectibles++;
        }

        while(it_tiles!=tiles.end())
        {
            auto cc = tiles[it_tiles - tiles.begin()];
            if(cc->getComponent<TileComponent>().tileId >= 0 && Collision::AABB(player->getComponent<ColliderComponent>(), cc->getComponent<ColliderComponent>()))
            {
                auto& rect = cc->getComponent<ColliderComponent>().entity->getComponent<ColliderComponent>().collider;
                auto& rect_p = player->getComponent<ColliderComponent>().collider;
                auto& pos_p = player->getComponent<TransformComponent>().position;
                auto& vel = player->getComponent<TransformComponent>().velocity;

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
            it_tiles++;
        }
        it_player++;
    }
    
    // auto it_enemy = enemies.begin();

    // while(it_enemy != enemies.end())
    // {        
    //     auto enemy = enemies[it_enemy - enemies.begin()];
    //     auto it_tiles = tiles.begin();        

    //     while(it_tiles!=tiles.end())
    //     {
    //         auto cc = tiles[it_tiles - tiles.begin()];
    //         if(cc->getComponent<TileComponent>().tileId != -1 && Collision::AABB(enemy->getComponent<ColliderComponent>(), cc->getComponent<ColliderComponent>()))
    //         {
    //             auto& rect = cc->getComponent<ColliderComponent>().entity->getComponent<ColliderComponent>().collider;
    //             auto& rect_p = enemy->getComponent<ColliderComponent>().collider;
    //             auto& pos_p = enemy->getComponent<TransformComponent>().position;
    //             auto& vel = enemy->getComponent<TransformComponent>().velocity;

    //             if(true){
    //                 if(rect.w<rect.h){
    //                     if(rect_p.x + rect_p.w/2 < rect.x){
    //                         pos_p.x = rect.x - rect_p.w - 2 - 8;
    //                     }

    //                     else if(rect_p.x + rect_p.w/2 >= rect.x){
    //                         pos_p.x = rect.x + rect.w + 2 - 8;
    //                     }
    //                 }
    //                 else{
    //                     if(rect_p.y + rect_p.h/2 < rect.y){
    //                         pos_p.y = rect.y - rect_p.h - 2 - 10;
    //                     }
    //                     else if(rect_p.y + rect_p.h/2 >= rect.y){
    //                         pos_p.y = rect.y + rect.h + 2 - 10;
    //                     }
    //                 }
    //             }
    //         }
    //         it_tiles++;
    //         Game::enemyChangeDirection(enemies[it_enemy - enemies.begin()]);
    //     }

    //     // it_player = players.begin();
    //     // while(it_player != players.end())
    //     // {
    //     //     auto player = players[it_player - players.begin()];
    //     //     if(Collision::AABB(player->getComponent<ColliderComponent>(), enemy->getComponent<ColliderComponent>()))
    //     //     {
    //     //         // Delete the player
    //     //     }
    //     //     else it_player++;
    //     // }
        
        
    //     it_enemy++;
    // }

    for(auto cc_:tiles)
    {
        if(cc_->getComponent<TileComponent>().tileId < 0)continue;
        ColliderComponent* cc = &cc_->getComponent<ColliderComponent>();
        for(auto& enemy:enemies){
            if(!Collision::EqualColliderComponent(enemy->getComponent<ColliderComponent>(), *cc))
            {
                if(Collision::AABB(enemy->getComponent<ColliderComponent>(), *cc))
                {

                    // if(cc->tag == "Tiles")
                    // {
                        auto& rect = cc->entity->getComponent<ColliderComponent>().collider;
                        auto& rect_p = enemy->getComponent<ColliderComponent>().collider;
                        auto& pos_p =enemy->getComponent<TransformComponent>().position;
                        auto& vel = enemy->getComponent<TransformComponent>().velocity;

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
                    // }
                    Game::enemyChangeDirection(enemy);
                    
                    
                }
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
    for(auto& c: collectibles){
        c->draw();
    }
    for(auto& e : enemies)
    {
        e->draw();
    }
    for(auto& p : players)
    {
        p->draw();
    }

//////////////////////
//////////////////////
//////////////////////
//////////////////////
// uncomment below to view collider boxes
//
    /*SDL_SetRenderDrawColor(renderer, 255, 0, 0, 120);
    for(auto cc:colliders){
        SDL_RenderDrawRect(renderer, &cc->collider);
    }*/

    
    

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
        auto& tile(Game::manager->addEntity());
        tile.addComponent<TileComponent>(row, col, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, id, mapScale);
        tile.addGroup(groupMap);
    }
    else if(id == -2)
    {
        auto& tile(Game::manager->addEntity());
        tile.addComponent<TileComponent>(row, col, SCREEN_WIDTH, OFFSET, 0, 0, id, mapScale);
        tile.addGroup(groupMap);
    }
    else
    {
        
        if(id%2 == 1)
        {
            
            auto& tile1(Game::manager->addEntity());
            tile1.addComponent<TileComponent>(row, col + DEFAULT_IMAGE_SIZE - ROWS_TO_SKIP_PYTHON, ROWS_TO_SKIP_PYTHON, DEFAULT_IMAGE_SIZE, 0, DEFAULT_IMAGE_SIZE - ROWS_TO_SKIP_PYTHON, id, mapScale); //    |
            tile1.addComponent<ColliderComponent>("Tiles");
            tile1.addGroup(groupMap);
        }

        if(id%4 >= 2)
        {
            auto& tile2(Game::manager->addEntity());
            tile2.addComponent<TileComponent>(row + DEFAULT_IMAGE_SIZE - ROWS_TO_SKIP_PYTHON, col, DEFAULT_IMAGE_SIZE, ROWS_TO_SKIP_PYTHON, DEFAULT_IMAGE_SIZE - ROWS_TO_SKIP_PYTHON, 0, id, mapScale);//    __
            tile2.addComponent<ColliderComponent>("Tiles");
            tile2.addGroup(groupMap);
        }

        if(id%16 >= 8)
        {
            auto& tile3(Game::manager->addEntity());
            tile3.addComponent<TileComponent>(row, col, DEFAULT_IMAGE_SIZE, ROWS_TO_SKIP_PYTHON, 0, 0, id, mapScale); // |
            tile3.addComponent<ColliderComponent>("Tiles");
            tile3.addGroup(groupMap);
        }

        if(id%8 >= 4)
        {
            auto& tile4(Game::manager->addEntity());                                                              // __
            tile4.addComponent<TileComponent>(row, col, ROWS_TO_SKIP_PYTHON, DEFAULT_IMAGE_SIZE, 0, 0, id, mapScale);// 
            tile4.addComponent<ColliderComponent>("Tiles");
            tile4.addGroup(groupMap);
        }
    }
    
}

vector<int> Game::checkTile(Entity* e){
    auto collider = e->getComponent<ColliderComponent>().collider;
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

void Game::enemyChangeDirection(Entity* enemy){

    //used rectangle collider_transform diff
    vector<int> tile = Game::checkTile(enemy);
    auto& pos = enemy->getComponent<TransformComponent>().position;
    auto& ai = enemy->getComponent<AIController>();
    vector<int> dir;
    for(int i = 0;i<4;i++)
    {
        if(Game::Maze->nodes[tile[0]][tile[1]]->neighbours[i]) dir.pb(i);
    }

    // cout<<"Info:\n tile: ("<<tile[0]<<", "<<tile[1]<<")\ndir: "<<"\n";
    // cout<<"dirs: \n";
    // for(int i = 0;i < dir.size();i++){
    //    cout<<dir[i]<<"\n";
    // }
    // cout<<"player: X = "<<pos.x<<", Y = "<<pos.y<<"\n";

    srand(time(0));
    int seed = rand();
    int fin_dir = dir[(seed % dir.size() + dir.size()) % dir.size()];
    ai.MovementDirection = fin_dir;
}

Entity& Game::addDragonBall(int tileX, int tileY, int star)
{
    Entity& collectible(Game::manager->addEntity());
    if(star >= 0)collectible.addComponent<TransformComponent>(TILE_SIZE/6 + tileX*TILE_SIZE, TILE_SIZE/6 + tileY*TILE_SIZE, TILE_SIZE/2, TILE_SIZE/2, 1.0);
    else if(star == -1)collectible.addComponent<TransformComponent>(TILE_SIZE/6 + tileX*TILE_SIZE, TILE_SIZE/6 + tileY*TILE_SIZE, 3*TILE_SIZE/2, 3*TILE_SIZE/2, 1.0);

    map <string, Animation*> anims;

    int srcX = 0;
    int srcY = 0;

    if(star >= 0)anims.insert(pair<string, Animation*>("Rotating", new Animation(10, 7, 100, srcX, srcY)));
    else if(star == -1)anims.insert(pair<string, Animation*>("Rotating", new Animation(10, 7, 300, srcX, srcY)));
    
    if(star >= 0)collectible.addComponent<SpriteComponent>("assets/spritesheets/full_coins.png", true, anims, "Rotating");
    else if(star == -1)collectible.addComponent<SpriteComponent>("assets/spritesheets/full_coins_large.png", true, anims, "Rotating");
    
    
    collectible.addComponent<ColliderComponent>("Coin");
    collectible.addGroup(groupCollectibles);
    return collectible;
}

int Game::bfs(int Tile1, int Tile2){
    bool vis[MAZE_COLUMNS*MAZE_ROWS];
    if(Tile1==Tile2) return -1;
    int x1 = Tile1%MAZE_COLUMNS;
    int x2 = Tile2%MAZE_COLUMNS;
    int y1 = Tile1/MAZE_COLUMNS;
    int y2 = Tile2/MAZE_COLUMNS;


    for(int i = 0;i<MAZE_ROWS*MAZE_COLUMNS;i++) vis[i] = false;
    queue<pair<int, int>> q;
    q.push({Tile1, -1});
    vis[Tile1] = true;


    while(!q.empty()){
        auto t = q.front();
        int t1 = t.first;
        q.pop();

        if(t.first == Tile2) {return t.second;}
        if(t.first == Tile1){
            if(Game::Maze->nodes[t1/MAZE_COLUMNS][t1%MAZE_COLUMNS]->neighbours[0] && !vis[t1-MAZE_COLUMNS]){q.push({t1 - MAZE_COLUMNS, 0}); vis[t1-MAZE_COLUMNS] = true;}
            if(Game::Maze->nodes[t1/MAZE_COLUMNS][t1%MAZE_COLUMNS]->neighbours[1] && !vis[t1-1]){q.push({t1 - 1, 1}); vis[t1-1] = true;}
            if(Game::Maze->nodes[t1/MAZE_COLUMNS][t1%MAZE_COLUMNS]->neighbours[2] && !vis[t1+MAZE_COLUMNS]){q.push({t1 + MAZE_COLUMNS, 2}); vis[t1+MAZE_COLUMNS] = true;}
            if(Game::Maze->nodes[t1/MAZE_COLUMNS][t1%MAZE_COLUMNS]->neighbours[3] && !vis[t1+1]){q.push({t1 + 1, 3}); vis[t1+1] = true;}
        }

        else{
            if(Game::Maze->nodes[t1/MAZE_COLUMNS][t1%MAZE_COLUMNS]->neighbours[0] && !vis[t1-MAZE_COLUMNS]){q.push({t1 - MAZE_COLUMNS, t.second}); vis[t1-MAZE_COLUMNS] = true;}
            if(Game::Maze->nodes[t1/MAZE_COLUMNS][t1%MAZE_COLUMNS]->neighbours[1] && !vis[t1-1]){q.push({t1 - 1,t.second}); vis[t1-1] = true;}
            if(Game::Maze->nodes[t1/MAZE_COLUMNS][t1%MAZE_COLUMNS]->neighbours[2] && !vis[t1+MAZE_COLUMNS]){q.push({t1 + MAZE_COLUMNS, t.second}); vis[t1+MAZE_COLUMNS] = true;}
            if(Game::Maze->nodes[t1/MAZE_COLUMNS][t1%MAZE_COLUMNS]->neighbours[3] && !vis[t1+1]){q.push({t1 + 1, t.second}); vis[t1+1] = true;}
        }
    }

}

/*bool Game::checkEnemyBoundingBox(Entity& enemy){

}*/


