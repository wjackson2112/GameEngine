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
    virtual ~Scene() = default;
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

    std::vector<Entity*> getEntities()
    {
        std::vector<Entity*> outEntities;
        for(auto& entity : entities)
        {
            outEntities.push_back(entity.get());
        }

        return outEntities;
    }

    template<class T>
    std::vector<T> getEntities()
    {
        std::vector<T> outEntities;
        for(auto& entity : entities)
        {
            if(auto castEntity = dynamic_cast<T*>(entity.get()))
            {
                outEntities.push_back(castEntity);
            }
        }

        return outEntities;
    }
};

#endif //SCENE_H