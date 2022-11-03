#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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

public:
    Scene();
    void draw();
    void update();
    void resolveCollisions();
};

#endif //SCENE_H