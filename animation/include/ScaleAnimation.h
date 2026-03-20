//
// Created by will on 9/21/25.
//

#ifndef SCALE_ANIMATION_H
#define SCALE_ANIMATION_H

#include "Transform.h"
#include "Animation.h"

class ScaleAnimation : public Animation
{
    glm::vec3 startScale, endScale;
    Transform* animatedTransform;

public:
    ScaleAnimation(Transform* animatedTransform, glm::vec3 endScale, float lengthSeconds,  IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationComplete, const std::string& completeIdentifier = "")
    : Animation(lengthSeconds, receiver, completeFunction, completeIdentifier)
    , animatedTransform(animatedTransform)
    , endScale(endScale) {}

    virtual void start();
    virtual void update(float deltaTime);
};

#endif //SCALE_ANIMATION_H
