#include "CompoundAnimation.h"

void CompoundAnimation::start()
{
    Animation::start();

    for(auto& compAnimEntry : animations)
        if(compAnimEntry.startTime == 0)
            compAnimEntry.animation->start();
}

void CompoundAnimation::skip()
{
    Animation::skip();

    for(auto& compAnimEntry : animations)
        compAnimEntry.animation->skip();
}

void CompoundAnimation::update(float deltaTime)
{
    Animation::update(deltaTime);

    for(auto it = animations.begin(); it != animations.end(); )
    {
        if(it->animation->hasFinished())
        {
            it = animations.erase(it);
        }
        else
        {
            ++it;
        }
    }

    for(auto& compAnimEntry : animations)
    {
        // Start new animations as their start time arrives
        if((compAnimEntry.startTime > (elapsedSeconds - deltaTime)) &&
           (compAnimEntry.startTime <= elapsedSeconds))
        {
            compAnimEntry.animation->start();
            compAnimEntry.animation->update(elapsedSeconds - compAnimEntry.startTime);
        }
        // Update animations that have a start time that has passed
        else if(compAnimEntry.startTime <= (elapsedSeconds - deltaTime))
        {
            compAnimEntry.animation->update(deltaTime);
        }
    }
}

void CompoundAnimation::lateUpdate(float deltaTime)
{
    Animation::lateUpdate(deltaTime);

    for(auto& compAnimEntry : animations)
        compAnimEntry.animation->lateUpdate(deltaTime);
}