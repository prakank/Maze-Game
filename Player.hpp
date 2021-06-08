#ifndef PLAYER_H
#define PLAYER_H

#include<map>
#include "game.cpp"
#include "ECS/Components.hpp"
#include "ECS/EntityComponentSystem.hpp"
#include "ECS/Animation.hpp"

class Player: public Entity{
public:

    int xpos, ypos, h, w;
    float sc;
    Player(Manager& m_manager, int xpos1 = 0, int ypos1 = 0, int w1 = DEFAULT_IMAGE_SIZE, int h1 = DEFAULT_IMAGE_SIZE, float sc1 = WINDOW_SCALE): Entity(m_manager){
        xpos = xpos1;
        ypos = ypos1;
        w = w1;
        h = h1;
        sc = sc1;
        
    }

    void init(){
        //manager = m_manager;
        //cout<<"been through here";
        this->addComponent<TransformComponent>(xpos, ypos, w, h, sc);

        map<string, Animation*> map1;
        map1.insert(pair<string, Animation*>("Idle_U", new Animation(0, 1, 100, 0, 0)));
        map1.insert(pair<string, Animation*>("Idle_L", new Animation(1, 1, 100, 0, 1)));
        map1.insert(pair<string, Animation*>("Idle_D", new Animation(2, 1, 100, 0, 2)));
        map1.insert(pair<string, Animation*>("Idle_R", new Animation(3, 1, 100, 0, 3)));
        this->addComponent<SpriteComponent>("assets/spritesheets/character1_all.png", true, map1, "Idle_D");

        this->addComponent<KeyboardController>();

        this->addComponent<ColliderComponent>("player");

        this->addGroup(groupPlayers);

    }









    
    int health;


};

#endif