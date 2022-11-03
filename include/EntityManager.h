//
// Created by Will on 7/25/2022.
//

#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>

#include "Entity.h"

class EntityManager
{
    static EntityManager* instance;
    std::vector<Entity*> entities;

    // This is a singleton so the constructor is private
    EntityManager() = default;
public:
    ~EntityManager();
    static EntityManager *getInstance();

    std::vector<Entity*> getEntities() { return entities; };

    void registerEntity(Entity* entity);
    void deregisterEntity(Entity* entity);
};

#endif //ENTITY_MANAGER_H
