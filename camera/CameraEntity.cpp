//
// Created by Will on 6/5/2024.
//

#include "CameraEntity.h"
#include "CameraComponent.h"

CameraEntity::CameraEntity()
{
    this->transform = glm::vec3(0.0f, 0.0f, 0.0f);
    addComponent<CameraComponent>(new CameraComponent());

    shouldUpdate = true;
}

CameraEntity::CameraEntity(Transform transform)
{
    this->transform = transform;
    addComponent<CameraComponent>(new CameraComponent());

    shouldUpdate = true;
}

void CameraEntity::update(float deltaTime)
{
    static float elapsedTime = 0.f;

    elapsedTime += deltaTime;

    Entity::update(deltaTime);
//    getComponent<CameraComponent>()->orbit(std::cos(elapsedTime), 0.f, 20.f);
}
