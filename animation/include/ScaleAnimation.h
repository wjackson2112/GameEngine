//
// Created by will on 9/21/25.
//

#ifndef SCALE_ANIMATION_H
#define SCALE_ANIMATION_H

#include "Transform.h"
#include "Animation.h"
#include "Entity.h"

class ScaleAnimation : public Animation
{
    glm::vec3 endScale;
    Transform* animatedTransform;
    glm::vec3 startScale;

public:
    ScaleAnimation(Entity* animatedEntity, glm::vec3 endScale, float lengthSeconds,  IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationCompleteWithId, const std::string& completeIdentifier = "")
    : Animation(lengthSeconds, animatedEntity, receiver, completeFunction, completeIdentifier)
    , animatedTransform(animatedEntity->getTransform())
    , endScale(endScale) {}

    virtual void start();
    virtual void update(float deltaTime);
};

#endif //SCALE_ANIMATION_H
