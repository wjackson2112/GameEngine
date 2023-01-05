#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <algorithm>
#include <iostream>

#include "Scene.h"
#include "CollisionComponentBase.h"
#include "EntityManager.h"
#include "AssetManager.h"
#include "InputManager.h"


Scene::Scene()
{
    postProcessor = new PostProcessor(AssetManager::getInstance()->loadShader("shaders\\screen.vert",
                                                                              "shaders\\screen.frag",
                                                                              nullptr,
                                                                              "screen"));
}

Scene::~Scene()
{
    std::vector<Entity*> entities = EntityManager::getInstance()->getEntitiesInScene(this);
    for(Entity* entity : entities)
    {
//        InputManager::getInstance()->deregisterReceiver((IInputReceiver*) entity);
        EntityManager::getInstance()->deregisterEntity(entity);
    }
}

void Scene::draw()
{
    // Sort by depth to ensure furthest back objects are drawn first
    // TODO: These entities should be made const
    EntityManager* entityManager = EntityManager::getInstance();
    std::vector<Entity*> entities = entityManager->getEntitiesInScene(this);
    std::stable_sort(entities.begin(), entities.end(), [](Entity* first, Entity* second)
    {
        return first->getTransform()->getPosition().z < second->getTransform()->getPosition().z;
    }); // TODO: I have no idea if this is better than just turning depth testing back on, check performance once text is implemented


    // Find the camera
    // TODO: This should probably be more intentional so multi camera can work
    if(!activeCamera)
    {
        for (Entity *entity: entities) {
            if (auto camComp = entity->getComponent<CameraComponentBase>())
            {
                activeCamera = camComp;
                break;
            }
        }
    }

    // Begin postprocessing
    postProcessor->begin();

    // Draw to the back buffer
    for(Entity* entity : entities)
    {
        Transform cameraWorldTransform = activeCamera->getWorldTransform();
        glm::mat4 cameraProjection = activeCamera->getProjection();
        entity->draw(glm::inverse(cameraWorldTransform.getModel()),
                     cameraProjection,
                     lightVector,
                     cameraWorldTransform.getPosition());
    }

    // End postprocessing
    postProcessor->end();
}

void Scene::update()
{
    static float deltaTime = 0.0f;
    static float lastFrame = 0.0f;

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    EntityManager* entityManager = EntityManager::getInstance();
    std::vector<Entity*> entities = entityManager->getEntitiesInScene(this);

    for(Entity* entity : entities)
    {
        if(!activeCamera)
            if(auto camComp = entity->getComponent<CameraComponentBase>())
                activeCamera = camComp;

        if(entity->receivesUpdates)
            entity->update(deltaTime);
    }

    // Cleanup any entities which have been marked as destroyed
    // Use a manual iterator here, so we can delete items mid-loop
    // TODO: Maybe this should move to the entity manager?
    auto it = entities.begin();
    while(it != entities.end())
    {
        Entity* entity = *(it++);
        if(entity->shouldBeDestroyed)
            entityManager->deregisterEntity(entity);
    }
}

void Scene::resolveCollisions()
{
    std::vector<Entity*> collisionEntities = std::vector<Entity*>();

    EntityManager* entityManager = EntityManager::getInstance();
    std::vector<Entity*> entities = entityManager->getEntitiesInScene(this);

    for(Entity* entity : entities)
    {
        collisionEntities.push_back(entity);
    }

    for(int i = 0; i < entities.size(); i++)
        for(int j = i + 1; j < entities.size(); j++)
            if(auto iColComp = entities[i]->getComponent<CollisionComponentBase>())
                if(auto jColComp = entities[j]->getComponent<CollisionComponentBase>())
                    iColComp->resolveIfCollided(jColComp);

    // Cleanup any entities which have been marked as destroyed
    // Use a manual iterator here, so we can delete items mid-loop
    auto it = entities.begin();
    while(it != entities.end())
    {
        Entity* entity = *(it++);
        if(entity->shouldBeDestroyed)
            entityManager->deregisterEntity(entity);
    }
}