//
// Created by Will on 2/7/2023.
//

#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <list>
#include <memory>
#include "Component.h"
#include "Animation.h"

class AnimationComponent : public Component
{
    std::list<std::unique_ptr<Animation>> animations;
public:
    void skipAll();
    void update(float deltaTime) override;
    void lateUpdate(float deltaTime) override;
    bool hasAnimations() { return !animations.empty(); }
    bool hasUnfinishedAnimations() {
        for(auto&& animation : animations)
            if(!animation->hasFinished())
                return true;
        return false;
    }

    template<typename T, typename... Args>
    T* addAndStart(Args... args)
    {
        T* animation = new T(args...);
        animation->start();
        animations.push_back(std::unique_ptr<T>(animation));
        receivesUpdates = true;
        return animation;
    }

    template<class T>
    std::vector<T> getAnimations()
    {
        std::vector<T> output;
        for(const auto& animation : animations)
        {
            if(auto castAnimation = dynamic_cast<T*>(animation.get()))
            {
                output.push_back(*castAnimation);
            }
        }

        return output;
    }
};

#endif //ANIMATION_COMPONENT_H
