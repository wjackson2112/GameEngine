//
// Created by Will on 2/7/2023.
//

#ifndef TRANSFORM_ANIMATION_H
#define TRANSFORM_ANIMATION_H

#include "Transform.h"
#include "Animation.h"

class TransformAnimation : public Animation
{
    Transform startTransform, endTransform;
    Transform* animatedTransform;

public:
    TransformAnimation(Transform* animatedTransform, Transform endTransform, float lengthSeconds, IAnimationCompleteReceiver* receiver = nullptr)
    : Animation(lengthSeconds, receiver)
    , animatedTransform(animatedTransform)
    , startTransform(*animatedTransform)
    , endTransform(endTransform) {}

    virtual void start();
    virtual void skip();
    virtual void update(float deltaTime);

    glm::vec3 getRemainingTranslation();
};

#endif //TRANSFORM_ANIMATION_H
