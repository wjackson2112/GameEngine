//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

#include "CameraComponent2D.h"
#include "OptionsManager.h"


CameraComponent2D::CameraComponent2D()
{
    OptionsManager::getInstance()->registerReceiver(this);

    // Orthographic Projection
    glm::vec2 viewportRes = OptionsManager::getInstance()->getViewportResolution();
    projection = glm::ortho(0.0f, viewportRes.x, viewportRes.y, 0.0f, -1.0f, 1.0f);
}

CameraComponent2D::~CameraComponent2D()
{
    OptionsManager::getInstance()->deregisterReceiver(this);
}

void CameraComponent2D::resolutionUpdated(glm::vec2 oldRes, glm::vec2 newRes)
{
    projection = glm::ortho(0.0f, newRes.x, newRes.y, 0.0f, -1.0f, 1.0f);
}
