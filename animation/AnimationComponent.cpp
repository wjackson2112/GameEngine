//
// Created by Will on 2/7/2023.
//

#include <algorithm>
#include "AnimationComponent.h"

void AnimationComponent::skipAll()
{
    for(auto&& animation : animations)
        animation->skip();

    animations.clear();
    receivesUpdates = false;
}

void AnimationComponent::update(float deltaTime)
{
    for(auto animIter = animations.begin(); animIter != animations.end();)
    {
        if((*animIter)->hasFinished())
        {
            animIter = animations.erase(animIter);
            continue;
        }

        if ((*animIter)->isRunning())
        {
            (*animIter)->update(deltaTime);
            animIter++;
        }
    }

    if(animations.empty())
        receivesUpdates = false;
}

void AnimationComponent::lateUpdate(float deltaTime)
{
    for(auto animIter = animations.begin(); animIter != animations.end();)
    {
        if((*animIter)->hasFinished())
        {
            animIter = animations.erase(animIter);
            continue;
        }

        if ((*animIter)->isRunning())
        {
            (*animIter)->lateUpdate(deltaTime);
            animIter++;
        }

    }

    if(animations.empty())
        receivesUpdates = false;
}