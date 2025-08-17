//
// Created by Will on 2/14/2023.
//

#ifndef IANIMATION_COMPLETE_RECEIVER_H
#define IANIMATION_COMPLETE_RECEIVER_H

#include <string>

class IAnimationCompleteReceiver
{
public:
    virtual ~IAnimationCompleteReceiver() = default;

    virtual void animationCompleteWithId(std::string identifier, Entity* animatedEntity) = 0;
};

#endif //IANIMATION_COMPLETE_RECEIVER_H
