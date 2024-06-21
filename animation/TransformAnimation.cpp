//
// Created by Will on 2/7/2023.
//

#include "TransformAnimation.h"
#include <iostream>

void TransformAnimation::start()
{
    Animation::start();
}

void TransformAnimation::skip()
{
    Animation::skip();
}

void TransformAnimation::update(float deltaTime)
{
    Animation::update(deltaTime);

    float frameElapsedSeconds = elapsedSeconds - prevElapsedSeconds;

    // Just transform by the bit of distance left, so we don't overshoot
    if(elapsedSeconds >= lengthSeconds)
        frameElapsedSeconds = frameElapsedSeconds - (elapsedSeconds - lengthSeconds);

    glm::vec3 totalMovement = endTransform.getPosition() - startTransform.getPosition();
    glm::vec3 movement = totalMovement * frameElapsedSeconds / lengthSeconds;
    animatedTransform->translate(movement);
}

glm::vec3 TransformAnimation::getRemainingTranslation()
{
    glm::vec3 totalMovement = endTransform.getPosition() - startTransform.getPosition();
    float timeLeft = lengthSeconds - elapsedSeconds;
    return totalMovement * timeLeft/lengthSeconds;
}
