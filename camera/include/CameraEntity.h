//
// Created by Will on 6/5/2024.
//

#ifndef CAMERA_ENTITY_H
#define CAMERA_ENTITY_H

#include "Entity.h"
#include "Transform.h"

class CameraEntity : public Entity
{
public:
    CameraEntity();
    CameraEntity(Transform transform);

    void update(float deltaTime) override;
};

#endif //CAMERA_ENTITY_H
