//
// Created by Will on 2/14/2023.
//

#ifndef IANIMATION_COMPLETE_RECEIVER_H
#define IANIMATION_COMPLETE_RECEIVER_H

#include <string>

class Entity;

class IAnimationCompleteReceiver
{
public:
    virtual ~IAnimationCompleteReceiver() = default;

    virtual void animationCompleteWithId(std::string identifier, Entity* animatedEntity) {};
};

#endif //IANIMATION_COMPLETE_RECEIVER_H
