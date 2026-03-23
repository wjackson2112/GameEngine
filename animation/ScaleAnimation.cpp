//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by will on 9/21/25.
//

#include "ScaleAnimation.h"
#include <iostream>

void ScaleAnimation::start()
{
    Animation::start();
    startScale = animatedTransform->getScale();
}

void ScaleAnimation::update(float deltaTime)
{
    Animation::update(deltaTime);

    float frameElapsedSeconds = elapsedSeconds - prevElapsedSeconds;

    // Just translate by the bit of distance left, so we don't overshoot
    if(elapsedSeconds >= lengthSeconds)
        frameElapsedSeconds = frameElapsedSeconds - (elapsedSeconds - lengthSeconds);

    glm::vec3 totalScaling = endScale - startScale;//endTransform.getScale() - startTransform.getScale();
    glm::vec3 scaling;

    glm::vec3 targetScaling = (totalScaling * elapsedSeconds / lengthSeconds) + startScale;
    glm::vec3 prevScaling = (totalScaling * prevElapsedSeconds / lengthSeconds) + startScale;

    if(prevScaling.x == 0 || prevScaling.y == 0 || prevScaling.z == 0) // Avoid division by zero
        scaling = targetScaling;
    else
        scaling = targetScaling / prevScaling;

    Transform frameTransform;
    frameTransform.scaleTo(scaling);

    // Allow scale to be picked up off of zero instead of getting stuck
    if(animatedTransform->getScale().x == 0 || animatedTransform->getScale().y == 0 || animatedTransform->getScale().z == 0)
        animatedTransform->scaleTo(scaling);
    else
        *animatedTransform = animatedTransform->compose(frameTransform);
}