//
// Created by Will on 7/19/2023.
//

#ifndef COLOR_ANIMATION_H
#define COLOR_ANIMATION_H

#include "Animation.h"
#include <glm/glm.hpp>
#include "Entity.h"
#include "SpriteComponent2D.h"

class ColorAnimation : public Animation
{
    glm::vec4 startColor, endColor;
    glm::vec4* animatedColor;

public:
    ColorAnimation(Entity* animatedEntity, glm::vec4 endColor, float lengthSeconds, IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationComplete)
    : Animation(lengthSeconds, animatedEntity, receiver, completeFunction)
    , animatedColor(&animatedEntity->getComponent<SpriteComponent2D>()->color)
    , startColor(animatedEntity->getComponent<SpriteComponent2D>()->color)
    , endColor(endColor){}

    virtual void start();
    virtual void skip();
    virtual void update(float deltaTime);
};

#endif //COLOR_ANIMATION_H
