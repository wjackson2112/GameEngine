//
// Created by Will on 2/7/2023.
//

#include <algorithm>
#include "AnimationComponent.h"

void AnimationComponent::addAndStart(Animation* newAnimation)
{
    animations.push_back(newAnimation);
    animations.back()->start();
    receivesUpdates = true;
}

void AnimationComponent::skipAll()
{
    for(auto animation : animations)
        animation->skip();

    for(auto animation : animations)
        delete animation;

    animations.clear();
    receivesUpdates = false;
}

void AnimationComponent::update(float deltaTime)
{
    // Snapshot the state of the animations before iterating
    // (to avoid issues where animations are added midloop)
    std::vector<Animation*> animationsCopy = animations;

    for(auto animIter = animationsCopy.begin(); animIter != animationsCopy.end();)
    {
        if ((*animIter)->isRunning())
            (*animIter)->update(deltaTime);

        if((*animIter)->hasFinished())
            animations.erase(std::remove(animations.begin(), animations.end(), *animIter), animations.end());
        animIter++;
    }

    if(animations.empty())
        receivesUpdates = false;
}