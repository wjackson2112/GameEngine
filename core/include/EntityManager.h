//
// Created by Will on 7/25/2022.
//

#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>

#include "Scene.h"
#include "Entity.h"

class EntityManager
{
    struct EntityManagerEntry
    {
        Entity* entity;
        Scene* scene;

        EntityManagerEntry(Scene* scene, Entity* entity) : scene(scene), entity(entity) {}
    };

    static EntityManager* instance;
    std::vector<EntityManagerEntry> entityEntries;

    // This is a singleton so the constructor is private
    EntityManager() = default;
public:
    ~EntityManager();
    static EntityManager *getInstance();

    std::vector<Entity*> getEntities();
    std::vector<Entity*> getEntitiesInScene(Scene* scene);
    Scene* getSceneForEntity(Entity* entity);

    void registerEntity(Scene* scene, Entity* entity);
    void deregisterEntity(Entity* entity);
};

#endif //ENTITY_MANAGER_H
