//
// Created by Will on 7/13/2022.
//

#include "CollisionComponent2DRound.h"
#include "CollisionComponent2DAABB.h"

Transform CollisionComponent2DRound::getCenterWorldTransform() {
    if(parent)
        return parent->getWorldTransform().compose(centerTransform);
    else
        return centerTransform;
}

void CollisionComponent2DRound::resolveIfCollided(CollisionComponentBase *other)
{
    if(auto* otherComp = dynamic_cast<CollisionComponent2DAABB*>(other))
    {
        otherComp->resolveIfCollided(this); // Let AABB resolve this
    }
}