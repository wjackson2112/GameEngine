//
// Created by Will on 7/13/2022.
//

#ifndef COLLISION_COMPONENT_2D_ROUND_H
#define COLLISION_COMPONENT_2D_ROUND_H

#include "CollisionComponentBase.h"

class CollisionComponent2DRound : public CollisionComponentBase
{
    float radius = 0.0f;
    Transform centerTransform;

public:
    CollisionComponent2DRound(ICollisionReceiver* receiver, float radius, Transform centerTransform)
    : radius(radius)
    , centerTransform(centerTransform)
    , CollisionComponentBase(receiver)
    { }

    inline float getRadius() { return radius; }
    Transform getCenterWorldTransform();

    // Start CollisionComponentBase
    void resolveIfCollided(CollisionComponentBase* other);
    // End CollisionComponentBase
};

#endif // COLLISION_COMPONENT_2D_ROUND_H
