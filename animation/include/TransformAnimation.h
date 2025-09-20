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
    Transform deltaTransform;
    Transform* animatedTransform;
    glm::vec3 startScale;


public:
    TransformAnimation(Entity* animatedEntity, Transform deltaTransform, float lengthSeconds,  IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationCompleteWithId, const std::string& completeIdentifier = "")
    : Animation(lengthSeconds, animatedEntity, receiver, completeFunction, completeIdentifier)
    , animatedTransform(animatedEntity->getTransform())
    , deltaTransform(deltaTransform) {}

    virtual void start();
    virtual void skip();
    virtual void update(float deltaTime);

    glm::vec3 getRemainingTranslation();
};

#endif //TRANSFORM_ANIMATION_H
