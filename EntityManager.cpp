//
// Created by Will on 7/25/2022.
//
#include "EntityManager.h"

#include <algorithm>

//TODO: This should use some kind o automatically managed pointers like shared_ptr
EntityManager* EntityManager::getInstance()
{
    if(!instance)
        instance = new EntityManager();
    return instance;
}

EntityManager::~EntityManager()
{
    for(Entity* entity : entities)
        delete entity;
}

void EntityManager::registerEntity(Entity *entity)
{
    entities.push_back(entity);
}

void EntityManager::deregisterEntity(Entity *entity)
{
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
}

EntityManager *EntityManager::instance = 0;