//
// Created by Will on 6/30/2022.
//

#ifndef COLLISION_COMPONENT_BASE_H
#define COLLISION_COMPONENT_BASE_H

#include "Entity.h"
#include "ICollisionReceiver.h"

class CollisionComponentBase : public Component
{
protected:
    ICollisionReceiver* receiver;

public:
    CollisionComponentBase(ICollisionReceiver* parent)
    {
        this->receiver = parent;
    }

    inline ICollisionReceiver* getReceiver() { return receiver; }

    virtual void resolveIfCollided(CollisionComponentBase* other) = 0;
};

#endif //COLLISION_COMPONENT_BASE_H
