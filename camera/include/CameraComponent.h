//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include <glm/glm.hpp>

#include "Entity.h"
#include "Transform.h"
#include "CameraComponentBase.h"

class CameraComponent : public CameraComponentBase
{
    float yawDegrees = 0.0f;
    float pitchDegrees = 0.0f;
    float rollDegrees = 0.0f;

public:
    CameraComponent() = default;
    explicit CameraComponent(Transform transform);

    void orbit(float yaw, float pitch, float distance);
    void lookAt(glm::vec3 target);
//    void draw(Entity* entity, glm::vec3 lightDir);
};

#endif // CAMERA_COMPONENT_H