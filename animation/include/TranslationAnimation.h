//
// Created by will on 9/21/25.
//

#ifndef TRANSLATION_ANIMATION_H
#define TRANSLATION_ANIMATION_H

#include "Transform.h"
#include "Animation.h"
#include "Entity.h"

class TranslationAnimation : public Animation
{
    glm::vec3 deltaTranslation;
    Transform* animatedTransform;

public:
    TranslationAnimation(Entity* animatedEntity, glm::vec3 deltaTranslation, float lengthSeconds,  IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationCompleteWithId, const std::string& completeIdentifier = "")
    : Animation(lengthSeconds, animatedEntity, receiver, completeFunction, completeIdentifier)
    , animatedTransform(animatedEntity->getTransform())
    , deltaTranslation(deltaTranslation) {}

    virtual void update(float deltaTime);

    glm::vec3 getRemainingTranslation();
};

#endif //TRANSLATION_ANIMATION_H
