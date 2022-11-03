#include "CameraComponent2D.h"

CameraComponent2D::CameraComponent2D()
{
    // Orthographic Projection
    projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
}
