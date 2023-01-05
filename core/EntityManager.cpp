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
    for(EntityManagerEntry entityEntry : entityEntries)
        delete entityEntry.entity;
}

std::vector<Entity*> EntityManager::getEntities()
{
    std::vector<Entity*> returnValue;

    for(EntityManagerEntry entityEntry : entityEntries)
        returnValue.push_back(entityEntry.entity);

    return returnValue;
}

std::vector<Entity*> EntityManager::getEntitiesInScene(Scene *scene)
{
    std::vector<Entity*> returnValue;

    for(EntityManagerEntry entityEntry : entityEntries)
        if(entityEntry.scene == scene)
            returnValue.push_back(entityEntry.entity);

    return returnValue;
}

Scene* EntityManager::getSceneForEntity(Entity* entity)
{
    Scene* returnValue = nullptr;

    for(EntityManagerEntry entityEntry : entityEntries)
    {
        if (entityEntry.entity == entity) {
            returnValue = entityEntry.scene;
            break;
        }
    }

    return returnValue;
}

void EntityManager::registerEntity(Scene *scene, Entity *entity)
{
    entityEntries.emplace_back(EntityManagerEntry(scene, entity));
}

void EntityManager::deregisterEntity(Entity *entity)
{
    for(auto it = entityEntries.begin(); it != entityEntries.end(); it++)
    {
        if (it->entity == entity) {
            delete it->entity;
            entityEntries.erase(it);
            break;
        }
    }
}

EntityManager *EntityManager::instance = 0;