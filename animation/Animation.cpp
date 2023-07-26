//
// Created by Will on 2/7/2023.
//

#include "Animation.h"

void Animation::start()
{
    state = RUNNING;
}

void Animation::skip()
{
    elapsedSeconds = lengthSeconds;
    state = FINISHED;
    if(receiver)
        ((*receiver).*completeFunction)(animatedEntity);
}

void Animation::update(float deltaTime)
{
    elapsedSeconds += deltaTime;
}

void Animation::lateUpdate(float deltaTime)
{
    if(elapsedSeconds > lengthSeconds)
    {
        state = FINISHED;
        if(receiver)
            ((*receiver).*completeFunction)(animatedEntity);
    }
}