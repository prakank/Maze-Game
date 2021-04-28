#include "EntityComponentSystem.hpp"

void Entity::addGroup(Group mGroup)
{
    groupBitset[mGroup] = true;
    manager.AddToGroup(this, mGroup);
}