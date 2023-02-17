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
    state = FINISHED;
    elapsedSeconds = lengthSeconds;
}

void Animation::update(float deltaTime)
{
    elapsedSeconds += deltaTime;

    if(elapsedSeconds > lengthSeconds)
    {
        state = FINISHED;
        if(receiver)
            receiver->animationComplete();
    }
}