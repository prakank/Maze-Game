#ifndef ENEMY_H
#define ENEMY_H
#include<map>
#include "game.cpp"
#include "ECS/Components.hpp"
#include "Constants.hpp"
#include "ECS/EntityComponentSystem.cpp"
#include "ECS/Animation.hpp"
#include "ECS/AIController.hpp"
#include "ECS/StatsComponent.hpp"

class Enemy: public Entity{
public:
    Enemy(Manager& mManager): Entity(mManager){}
    void init() override{
        this->addComponent<TransformComponent>(5, 5, DEFAULT_IMAGE_SIZE*2,
                                                 DEFAULT_IMAGE_SIZE*2, 1.0/2);
        this->getComponent<TransformComponent>().tag = ENEMY;
        map<string, Animation*> map1;
         map1.insert(pair<string, Animation*>("Idle_U", new Animation(0, 1, 100, 0, 0)));
        map1.insert(pair<string, Animation*>("Idle_L", new Animation(1, 1, 100, 0, DEFAULT_IMAGE_SIZE*2)));
        map1.insert(pair<string, Animation*>("Idle_D", new Animation(2, 1, 100, 0, 2 * DEFAULT_IMAGE_SIZE*2)));
        map1.insert(pair<string, Animation*>("Idle_R", new Animation(3, 1, 100, 0, 3 * DEFAULT_IMAGE_SIZE*2)));
        map1.insert(pair<string, Animation*>("Walk_U", new Animation(4, 9, 100, 15 * DEFAULT_IMAGE_SIZE*2, 0)));
        map1.insert(pair<string, Animation*>("Walk_L", new Animation(5, 9, 100, 15 * DEFAULT_IMAGE_SIZE*2, DEFAULT_IMAGE_SIZE*2)));
        map1.insert(pair<string, Animation*>("Walk_D", new Animation(6, 9, 100, 15 * DEFAULT_IMAGE_SIZE*2, 2 * DEFAULT_IMAGE_SIZE*2)));
        map1.insert(pair<string, Animation*>("Walk_R", new Animation(7, 9, 100, 15 * DEFAULT_IMAGE_SIZE*2, 3 * DEFAULT_IMAGE_SIZE*2)));
        this->addComponent<SpriteComponent>("assets/spritesheets/character1_all.png", true, map1, "Idle_D"); 
        this->addComponent<ColliderComponent>("Player");
        this->addComponent<AIController>();       
        this->addGroup(groupEnemies);
    }

    




};

#endif