//
// Created by Will on 2/7/2023.
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Entity.h"
#include "IAnimationCompleteReceiver.h"

typedef void (Entity::*AnimDelegate)();

enum AnimationState
{
    WAITING,
    RUNNING,
    FINISHED
};

class Animation
{
protected:
    AnimationState state;
    float lengthSeconds;
    float elapsedSeconds;

    IAnimationCompleteReceiver* receiver = nullptr;
public:

    Animation(float lengthSeconds, IAnimationCompleteReceiver* receiver)
    : state(WAITING)
    , lengthSeconds(lengthSeconds)
    , elapsedSeconds(0.0f)
    , receiver(receiver) {}

    bool isRunning() { return state == RUNNING; }
    bool hasFinished() { return state == FINISHED; }

    virtual void start();
    virtual void skip();
    virtual void update(float deltaTime);
    virtual void lateUpdate(float deltaTime);
};

#endif //ANIMATION_H
