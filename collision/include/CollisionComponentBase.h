//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

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
    bool active = true;

public:
    CollisionComponentBase(ICollisionReceiver* parent)
    {
        this->receiver = parent;
    }

    inline ICollisionReceiver* getReceiver() { return receiver; }
    inline void activate() { active = true; }
    inline void deactivate() { active = false; }
    inline bool isActive() { return active; }

    virtual void resolveIfCollided(CollisionComponentBase* other) = 0;
};

#endif //COLLISION_COMPONENT_BASE_H
