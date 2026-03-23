//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by will on 9/21/25.
//

#include "TranslationAnimation.h"

void TranslationAnimation::update(float deltaTime)
{
    Animation::update(deltaTime);

    float frameElapsedSeconds = elapsedSeconds - prevElapsedSeconds;

    // Just translate by the bit of distance left, so we don't overshoot
    if(elapsedSeconds >= lengthSeconds)
        frameElapsedSeconds = frameElapsedSeconds - (elapsedSeconds - lengthSeconds);

    glm::vec3 frameTranslation = deltaTranslation * frameElapsedSeconds / lengthSeconds;

    Transform frameTransform;
    frameTransform.setPosition(frameTranslation);
    *animatedTransform = animatedTransform->compose(frameTransform);
}

glm::vec3 TranslationAnimation::getRemainingTranslation()
{
    //glm::vec3 totalMovement = endTransform.getPosition() - startTransform.getPosition();
    float timeLeft = lengthSeconds - elapsedSeconds;
    return deltaTranslation * timeLeft/lengthSeconds;
}