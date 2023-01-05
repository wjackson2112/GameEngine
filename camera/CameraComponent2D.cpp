#include "CameraComponent2D.h"
#include "OptionsManager.h"

CameraComponent2D::CameraComponent2D()
{
    // Orthographic Projection
    glm::vec2 viewportRes = OptionsManager::getInstance()->getViewportResolution();
    projection = glm::ortho(0.0f, viewportRes.x, viewportRes.y, 0.0f, -1.0f, 1.0f);
}
