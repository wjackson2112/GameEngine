//
// Created by Will on 2/14/2023.
//

#ifndef IANIMATION_COMPLETE_RECEIVER_H
#define IANIMATION_COMPLETE_RECEIVER_H

class IAnimationCompleteReceiver
{
public:
    virtual void animationComplete(Entity* animatedEntity) {};
};

#endif //IANIMATION_COMPLETE_RECEIVER_H
