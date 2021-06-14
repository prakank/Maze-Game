#ifndef ENEMY_H
#define ENEMY_H
#include<map>
#include "game.cpp"
#include "ECS/Components.hpp"
#include "ECS/EntityComponentSystem.cpp"
#include "ECS/Animation.hpp"
#include "ECS/AIController.hpp"

class Enemy: public Entity{
public:
    Enemy(Manager& mManager): Entity(mManager){}
    void init() override{
        this->addComponent<TransformComponent>(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, DEFAULT_IMAGE_SIZE*2,
                                                 DEFAULT_IMAGE_SIZE*2, 1.0/2);

        map<string, Animation*> map1;
        map1.insert(pair<string, Animation*>("Idle_U", new Animation(0, 1, 100, 0, 0)));
        map1.insert(pair<string, Animation*>("Idle_L", new Animation(1, 1, 100, 0, 1)));
        map1.insert(pair<string, Animation*>("Idle_D", new Animation(2, 1, 100, 0, 2)));
        map1.insert(pair<string, Animation*>("Idle_R", new Animation(3, 1, 100, 0, 3)));
        map1.insert(pair<string, Animation*>("Walk_U", new Animation(4, 9, 100, 15, 0)));
        map1.insert(pair<string, Animation*>("Walk_L", new Animation(5, 9, 100, 15, 1)));
        map1.insert(pair<string, Animation*>("Walk_D", new Animation(6, 9, 100, 15, 2)));
        map1.insert(pair<string, Animation*>("Walk_R", new Animation(7, 9, 100, 15, 3)));
        this->addComponent<SpriteComponent>("assets/spritesheets/character1_all.png", true, map1, "Idle_D");
        this->addComponent<ColliderComponent>("Player");
        this->addComponent<AIController>();
    }

    




};

#endif