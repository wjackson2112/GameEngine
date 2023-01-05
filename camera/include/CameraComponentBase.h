#ifndef CAMERA_COMPONENT_BASE_H
#define CAMERA_COMPONENT_BASE_H

#include <glm/glm.hpp>

#include "Component.h"
#include "Entity.h"
#include "Transform.h"

class CameraComponentBase : public Component
{
protected:
    Transform transform;
    glm::mat4 projection;

public:
    CameraComponentBase() = default;
    CameraComponentBase(Transform transform) : transform(transform) {}

//    void draw(Entity* entity, glm::vec3 lightDir);
    Transform getTransform() { return transform; }
    glm::mat4 getProjection() { return projection; }
};

#endif //CAMERA_COMPONENT_BASE_H
