//
// Created by Will on 2/7/2023.
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include "Entity.h"
#include "IAnimationCompleteReceiver.h"

typedef void (IAnimationCompleteReceiver::*AnimCompleteFunction)(Entity* AnimatedEntity);

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
    float prevElapsedSeconds;

    Entity* animatedEntity;
    IAnimationCompleteReceiver* receiver = nullptr;
    AnimCompleteFunction completeFunction;
public:

    Animation(float lengthSeconds, Entity* animatedEntity, IAnimationCompleteReceiver* receiver = nullptr, AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationComplete)
    : state(WAITING)
    , lengthSeconds(lengthSeconds)
    , elapsedSeconds(0.0f)
    , animatedEntity(animatedEntity)
    , receiver(receiver)
    , completeFunction(completeFunction) {}

    bool isRunning() { return state == RUNNING; }
    bool hasFinished() { return state == FINISHED; }

    virtual void start();
    virtual void skip();
    virtual void update(float deltaTime);
    virtual void lateUpdate(float deltaTime);
};

#endif //ANIMATION_H
