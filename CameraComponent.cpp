#include "CameraComponent.h"

#include <iostream>

#include "Entity.h"
#include "Transform.h"
#include "GraphicsComponent.h"

CameraComponent::CameraComponent(Transform transform)
: CameraComponentBase(transform)
{
    projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
}

void CameraComponent::orbit(float yaw, float pitch, float distance)
{
    yawDegrees += yaw;
    pitchDegrees += pitch;

    yawDegrees = yawDegrees > 360.f ? yawDegrees - 360.f : yawDegrees;
    yawDegrees = yawDegrees < 0.f ? yawDegrees + 360.f : yawDegrees;

    pitchDegrees = pitchDegrees > 90.f ? 90.f : pitchDegrees;
    pitchDegrees = pitchDegrees < -90.f ? -90.f : pitchDegrees;

    Transform outTransform = Transform(); 
    outTransform.rotate(yawDegrees, glm::vec3(0.0f, 1.0f, 0.0f));
    outTransform.rotate(pitchDegrees, glm::vec3(1.0f, 0.0f, 0.0f));
    outTransform.translate(glm::vec3(0.0f, 0.0f, distance));
    transform = outTransform;
}

void CameraComponent::lookAt(glm::vec3 target)
{
    // Convert the target to local camera coordinates
    glm::vec3 cameraTarget = parent->getTransform()->getPosition() - target;
    transform.lookAt(cameraTarget);

	// glm::mat4 lookView = glm::lookAt(transform.getPosition(), cameraTarget, glm::vec3(0.0f, 1.0f, 0.0f));
    // transform.setModel(glm::inverse(lookView));
}

//void CameraComponent::draw(Entity* entity, glm::vec3 lightDir)
//{
//    Transform worldTransform = getWorldTransform();
//    entity->draw(glm::inverse(worldTransform.getModel()), projection, lightDir, worldTransform.getPosition());
//}