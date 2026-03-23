//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by will on 9/21/25.
//

#ifndef TRANSLATION_ANIMATION_H
#define TRANSLATION_ANIMATION_H

#include "Transform.h"
#include "Animation.h"

class TranslationAnimation : public Animation
{
    glm::vec3 deltaTranslation;
    Transform* animatedTransform;

public:
    TranslationAnimation(Transform* animatedTransform, glm::vec3 deltaTranslation, float lengthSeconds,  IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationComplete, const std::string& completeIdentifier = "")
    : Animation(lengthSeconds, receiver, completeFunction, completeIdentifier)
    , animatedTransform(animatedTransform)
    , deltaTranslation(deltaTranslation) {}

    virtual void update(float deltaTime);

    glm::vec3 getRemainingTranslation();
};

#endif //TRANSLATION_ANIMATION_H
