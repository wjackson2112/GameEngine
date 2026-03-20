//
// Created by Will on 8/22/2024.
//

#ifndef COMPOUND_ANIMATION_H
#define COMPOUND_ANIMATION_H

#include <list>
#include "Animation.h"

struct CompoundAnimationEntry
{
    float startTime;
    std::unique_ptr<Animation> animation;

    CompoundAnimationEntry() : startTime(0.0f), animation(nullptr) {}
    CompoundAnimationEntry(float startTime, std::unique_ptr<Animation> animation)
    : startTime(startTime), animation(std::move(animation)) {}
};

class CompoundAnimation : public Animation
{
    std::list<CompoundAnimationEntry> animations;
public:
    CompoundAnimation(float lengthSeconds, IAnimationCompleteReceiver* receiver = nullptr,
                      AnimCompleteFunction completeFunction = &IAnimationCompleteReceiver::animationComplete,
                      const std::string& completeIdentifier = "")
    : Animation(lengthSeconds, receiver, completeFunction, completeIdentifier) {};

    template<typename T, typename... Args>
    T* addAnimation(float startTime, Args... args)
    {
        T* animation = new T(args...);
        animations.push_back(CompoundAnimationEntry(startTime,
                                                      std::unique_ptr<T>(animation)));
        return animation;
    }

    // Animation Interface
    void start() override;
    void skip() override;
    void update(float deltaTime) override;
    void lateUpdate(float deltaTime) override;
};

#endif