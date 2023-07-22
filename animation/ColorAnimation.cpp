//
// Created by Will on 7/19/2023.
//

#include "ColorAnimation.h"

void ColorAnimation::start()
{
    Animation::start();
}

void ColorAnimation::skip()
{
    Animation::skip();
}

void ColorAnimation::update(float deltaTime)
{
    Animation::update(deltaTime);

    // Just adjust by the bit of change left, so we don't overshoot
    if(elapsedSeconds >= lengthSeconds)
        deltaTime = deltaTime - (elapsedSeconds - lengthSeconds);

    glm::vec4 totalChange = endColor - startColor;
    glm::vec4 change = totalChange * deltaTime / lengthSeconds;
    *animatedColor += change;
}