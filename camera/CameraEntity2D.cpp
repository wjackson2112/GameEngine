//
// Created by Will on 6/9/2022.
//

#include "CameraEntity2D.h"
#include "CameraComponent2D.h"

CameraEntity2D::CameraEntity2D()
{
    this->transform = glm::vec3(0.0f, 0.0f, 0.0f);
    addComponent(new CameraComponent2D());
}

CameraEntity2D::CameraEntity2D(Transform transform)
{
    this->transform = transform;
    addComponent(new CameraComponent2D());
}