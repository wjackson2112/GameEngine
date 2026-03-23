//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 7/19/2023.
//

#ifndef COLOR_ANIMATION_H
#define COLOR_ANIMATION_H

#include "Animation.h"
#include <glm/glm.hpp>

class ColorAnimation : public Animation
{
    glm::vec4 startColor, endColor;
    glm::vec4* animatedColor;

public:
    ColorAnimation(glm::vec4* animatedColor, glm::vec4 endColor, float lengthSeconds, IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationComplete)
    : Animation(lengthSeconds, receiver, completeFunction)
    , animatedColor(animatedColor)
    , endColor(endColor){}

    virtual void start();
    virtual void update(float deltaTime);
};

#endif //COLOR_ANIMATION_H
