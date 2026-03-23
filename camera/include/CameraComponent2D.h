//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 6/9/2022.
//

#ifndef CAMERA_COMPONENT_2D_H
#define CAMERA_COMPONENT_2D_H

#include "CameraComponentBase.h"
#include "IOptionsReceiver.h"

class CameraComponent2D : public CameraComponentBase, public IOptionsReceiver
{
public:
    CameraComponent2D();
    ~CameraComponent2D();

    //IOptionsReceiver
    void resolutionUpdated(glm::vec2 oldRes, glm::vec2 newRes);
};

#endif //CAMERA_COMPONENT_2D_H
