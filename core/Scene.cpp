#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define GL_GLEXT_PROTOTYPES
#define EGL_EGLEXT_PROTOTYPES
#else
#include <glad/glad.h>
#endif
#include <GLFW\glfw3.h>

#include <algorithm>
#include <iostream>

#include "Scene.h"
#include "CollisionComponentBase.h"
#include "AssetManager.h"
#include "InputManager.h"


Scene::Scene()
{
    postProcessor = new PostProcessor(AssetManager::getInstance()->loadShader("shaders\\screen.vert",
                                                                              "shaders\\screen.frag",
                                                                              nullptr,
                                                                              "screen"));
}

void Scene::draw()
{
//    // Sort by depth to ensure furthest back objects are drawn first
//    // TODO: These entities should be made const
//    EntityManager* entityManager = EntityManager::getInstance();
//    std::vector<Entity*> entities = entityManager->getEntitiesInScene(*this);

    // TODO: Removed this and turned on depth testing
    //       Keeping it here so it can be used to depth sort _transparent_ objects later
    //       After blending is implemented - https://learnopengl.com/Advanced-OpenGL/Blending
//    std::stable_sort(entities.begin(), entities.end(), [](Entity* first, Entity* second)
//    {
//        return first->getWorldTransform().getPosition().z < second->getWorldTransform().getPosition().z;
//    }); // TODO: I have no idea if this is better than just turning depth testing back on, check performance once text is implemented


    // Find the camera
    // TODO: This should probably be more intentional so multi camera can work
    if(!activeCamera)
    {
        for (const auto& entity: entities)
        {
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
    for (const auto& entity: entities)
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

//    EntityManager* entityManager = EntityManager::getInstance();
//    std::vector<Entity*> entities = entityManager->getEntitiesInScene(*this);

    for (const auto& entity: entities)
    {
        if(entity->receivesUpdates)
            entity->earlyUpdate(deltaTime);
    }

//    entities = entityManager->getEntitiesInScene(*this);

    for (const auto& entity: entities)
    {
        // Make sure this entity still exists
//        std::vector<Entity*> currentEntities = entityManager->getEntitiesInScene(*this);
//        if(std::find(currentEntities.begin(), currentEntities.end(), entity) == currentEntities.end())
//            continue;

        if(!activeCamera)
            if(auto camComp = entity->getComponent<CameraComponentBase>())
                activeCamera = camComp;

        if(entity->receivesUpdates)
            entity->update(deltaTime);
    }

//    entities = entityManager->getEntitiesInScene(*this);

    for (const auto& entity: entities)
    {
        // Make sure this entity still exists
//        std::vector<Entity*> currentEntities = entityManager->getEntitiesInScene(*this);
//        if(std::find(currentEntities.begin(), currentEntities.end(), entity) == currentEntities.end())
//            continue;

        if(entity->receivesUpdates)
            entity->lateUpdate(deltaTime);
    }

    // Cleanup any entities which have been marked as destroyed
    // Use a manual iterator here, so we can delete items mid-loop
    // TODO: Maybe this should move to the entity manager?
    auto it = entities.begin();
    while(it != entities.end())
    {
        auto next_it = it; ++next_it;
        if(it->get()->shouldBeDestroyed)
            entities.erase(it);
        it = next_it;
    }
}

void Scene::resolveCollisions()
{
    std::vector<Entity*> collisionEntities = std::vector<Entity*>();

//    EntityManager* entityManager = EntityManager::getInstance();
//    std::vector<Entity*> entities = entityManager->getEntitiesInScene(*this);

    for (const auto& entity: entities)
    {
        collisionEntities.push_back(entity.get());
    }

//    for(int i = 0; i < entities.size(); i++)
    for(auto it = entities.begin(); it != entities.end(); it++)
    {
        if(!it->get()->receivesUpdates)
            continue;

//        for (int j = i + 1; j < entities.size(); j++)
        auto other_it = it; other_it++;
        while(other_it != entities.end())
        {
            if(!other_it->get()->receivesUpdates)
            {
                other_it++;
                continue;
            }

            std::vector<CollisionComponentBase *> iComponents = it->get()->getComponents<CollisionComponentBase>();
            std::vector<CollisionComponentBase *> jComponents = other_it->get()->getComponents<CollisionComponentBase>();
            for (auto &iComponent: iComponents)
                for (auto &jComponent: jComponents)
                    iComponent->resolveIfCollided(jComponent);

            other_it++;
        }
    }

    // Cleanup any entities which have been marked as destroyed
    // Use a manual iterator here, so we can delete items mid-loop
    auto it = entities.begin();
    while(it != entities.end())
    {
        auto next_it = it; ++next_it;
        if(it->get()->shouldBeDestroyed)
            entities.erase(it);
        it = next_it;
    }
}

//template<typename T, typename... Args>
//void Scene::addEntity(Args... args)
