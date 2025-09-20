//
// Created by Will on 2/7/2023.
//

#include "TransformAnimation.h"
#include <iostream>
#include <cmath>

void TransformAnimation::start()
{
    Animation::start();

    startScale = animatedTransform->getScale();
}

void TransformAnimation::skip()
{
    Animation::skip();
}

void TransformAnimation::update(float deltaTime)
{
    Animation::update(deltaTime);

    float frameElapsedSeconds = elapsedSeconds - prevElapsedSeconds;

    // Just transform by the bit of distance left, so we don't overshoot
    if(elapsedSeconds >= lengthSeconds)
        frameElapsedSeconds = frameElapsedSeconds - (elapsedSeconds - lengthSeconds);

    // glm::vec3 origScale = animatedTransform->getScale();
    // if(origScale.x == 0 || origScale.y == 0 || origScale.z == 0)
    //     animatedTransform->scaleTo(glm::vec3(1.0));
    // else
    //     animatedTransform->scaleBy(glm::vec3(1.0)/origScale); // Return to normal scale before translate

    glm::vec3 totalMovement = deltaTransform.getPosition();//endTransform.getPosition() - startTransform.getPosition();
    glm::vec3 movement = totalMovement * frameElapsedSeconds / lengthSeconds;
    // animatedTransform->translate(movement);d
    //
    // animatedTransform->scaleBy(origScale/glm::vec3(1.0));


    glm::vec3 totalScaling = deltaTransform.getScale() - startScale;//endTransform.getScale() - startTransform.getScale();
    glm::vec3 scaling = glm::vec3(1.0f);
    if(totalScaling != glm::vec3(0))
    {
        glm::vec3 targetScaling = (totalScaling * elapsedSeconds / lengthSeconds) + startScale;
        glm::vec3 prevScaling = (totalScaling * prevElapsedSeconds / lengthSeconds) + startScale;
        scaling = targetScaling / prevScaling;

        if(prevScaling.x == 0 || prevScaling.y == 0 || prevScaling.z == 0)
            scaling = targetScaling;

        // std::cout << prevScaling.x << " " << prevScaling.y << " " << prevScaling.z << std::endl;
        // std::cout << targetScaling.x << " " << targetScaling.y << " " << targetScaling.z << std::endl;
        // std::cout << scaling.x << " " << scaling.y << " " << scaling.z << std::endl;
        // std::cout << std::endl;
    }

    Transform modTransform;
    modTransform.setPosition(movement);
    modTransform.scaleTo(scaling);
    *animatedTransform = animatedTransform->compose(modTransform);


    // glm::vec3 origScale = animatedTransform->getScale();
    // animatedTransform->scaleTo(glm::vec3(1.0f)); // Return to normal scale before translate
    //
    // Transform startPosTrans = startTransform;
    // startPosTrans.scaleTo(glm::vec3(1.0f));
    // glm::vec3 startPos = startPosTrans.getPosition();
    //
    // Transform endPosTrans = endTransform;
    // endPosTrans.scaleTo(glm::vec3(1.0f));
    // glm::vec3 endPos = endPosTrans.getPosition();
    //
    // glm::vec3 totalMovement = endPos - startPos;
    // glm::vec3 movement = totalMovement * frameElapsedSeconds / lengthSeconds;
    // animatedTransform->translate(movement);
    //
    // glm::vec3 totalScaling = endTransform.getScale() - startTransform.getScale();
    // glm::vec3 scaling = (totalScaling * elapsedSeconds / lengthSeconds) + startTransform.getScale();
    //
    // animatedTransform->scaleTo(origScale);
    // animatedTransform->scaleTo(scaling); // Scale back to target


}

glm::vec3 TransformAnimation::getRemainingTranslation()
{
    //glm::vec3 totalMovement = endTransform.getPosition() - startTransform.getPosition();
    float timeLeft = lengthSeconds - elapsedSeconds;
    return deltaTransform.getPosition() * timeLeft/lengthSeconds;
}
