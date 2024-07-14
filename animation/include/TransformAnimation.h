//
// Created by Will on 2/7/2023.
//

#ifndef TRANSFORM_ANIMATION_H
#define TRANSFORM_ANIMATION_H

#include "Transform.h"
#include "Animation.h"
#include "Entity.h"

class TransformAnimation : public Animation
{
    Transform startTransform, endTransform;
    Transform* animatedTransform;

public:
    TransformAnimation(Entity* animatedEntity, Transform endTransform, float lengthSeconds,  IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationCompleteWithId, const std::string& completeIdentifier = "")
    : Animation(lengthSeconds, animatedEntity, receiver, completeFunction, completeIdentifier)
    , animatedTransform(animatedEntity->getTransform())
    , startTransform(*animatedEntity->getTransform())
    , endTransform(endTransform) {}

    virtual void start();
    virtual void skip();
    virtual void update(float deltaTime);

    glm::vec3 getRemainingTranslation();
};

#endif //TRANSFORM_ANIMATION_H
