//
// Created by Will on 2/7/2023.
//

#ifndef ANIMATION_COMPONENT_H
#define ANIMATION_COMPONENT_H

#include <vector>
#include "Component.h"
#include "Animation.h"

class AnimationComponent : public Component
{
    std::vector<Animation*> animations;
public:
    void addAndStart(Animation* newAnimation);
    void skipAll();
    void update(float deltaTime);
    void lateUpdate(float deltaTime);
    bool hasAnimations() { return !animations.empty(); }

    template<class T>
    std::vector<T> getAnimations()
    {
        std::vector<T> output;
        for(auto animation : animations)
        {
            if(auto castAnimation = dynamic_cast<T*>(animation))
            {
                output.push_back(*castAnimation);
            }
        }

        return output;
    }
};

#endif //ANIMATION_COMPONENT_H
