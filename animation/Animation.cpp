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
    float deltaTime = lengthSeconds - elapsedSeconds;

    update(deltaTime);
    lateUpdate(deltaTime);
}

void Animation::update(float deltaTime)
{
    prevElapsedSeconds = elapsedSeconds;
    elapsedSeconds += deltaTime;
}

void Animation::lateUpdate(float deltaTime)
{
    if(elapsedSeconds >= lengthSeconds)
    {
        state = FINISHED;
        if(receiver && completeFunction)
            (receiver->*completeFunction)(completeIdentifier, animatedEntity);
    }
}