#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
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

    std::vector<std::unique_ptr<Entity>> entities;

public:
    Scene();
    virtual ~Scene();
    void draw();
    void update();
    void resolveCollisions();


    template<typename T, typename... Args>
    T* addEntity(Args... args)
    {
        T* entity = new T(args...);
        entities.push_back(std::unique_ptr<T>(entity));
        entities.back()->setOwningScene(this);

        return entity;
    }
};

#endif //SCENE_H