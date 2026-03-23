//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 6/9/2022.
//

#ifndef CAMERA_ENTITY_H
#define CAMERA_ENTITY_H

#include "Entity.h"
#include "Transform.h"

class CameraEntity2D : public Entity
{
public:
    CameraEntity2D();
    CameraEntity2D(Transform transform);
};

#endif //CAMERA_ENTITY_H
