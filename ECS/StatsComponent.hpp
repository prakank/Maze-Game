#ifndef STATS_COMPONENT_HPP
#define STATS_COMPONENT_HPP

#include<algorithm>
#include "Components.hpp"
#include "../game.hpp"
#include "EntityComponentSystem.hpp"
#include "TransformComponent.hpp"

class StatsComponent: public Component{
    int health_max;
    bool isPlayer;
    bool hasDragonBall[8] = {false, false, false, false, false, false, false, false};
    int health;
    int ki;
    int timeOfLastHit = SDL_GetTicks();
    int timeFromLastHit;

    StatsComponent(int health_init, bool isPlayer_init){
        isPlayer = isPlayer_init;
        health = health_init;
        health_max = health_init;
    }

    void update(){
        timeFromLastHit = (SDL_GetTicks() - timeOfLastHit)/1000;
        if(timeFromLastHit > 8){
            health = max(health + 75, health_max);
        }
    }

}




#endif
