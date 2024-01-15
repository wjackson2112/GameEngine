#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <memory>

#include "Entity.h"
#include "CameraComponentBase.h"
#include "Shader.h"
#include "Texture2D.h"
#include "PostProcessor.h"

class Scene
{
    CameraComponentBase* activeCamera = nullptr;
    glm::vec3 lightVector = glm::vec3(1.0f, -1.0f, 1.0f);

    PostProcessor* postProcessor;

    std::map<std::string, std::unique_ptr<Entity>> entities;

public:
    Scene();
    virtual ~Scene();
    void draw();
    void update();
    void resolveCollisions();


    template<typename T, typename... Args>
    void addEntity(std::string key, Args... args)
    {
        entities.insert({key, std::make_unique<T>(args...)});
        entities[key]->setOwningScene(this);
    }

    template<typename T>
    T* getEntity(const std::string& key)
    {
        if(entities.count(key) == 0)
            return nullptr;

        if(auto entity = dynamic_cast<T*>(entities[key].get()))
            return entity;

        return nullptr;
    }
};

#endif //SCENE_H