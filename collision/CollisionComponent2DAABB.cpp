//  Copyright (c) 2026 William Jackson
//  Licensed under the MIT License

//
// Created by Will on 7/1/2022.
//

#include "CollisionComponent2DAABB.h"
#include "CollisionComponent2DRound.h"

void CollisionComponent2DAABB::resolveIfCollided(CollisionComponentBase* other)
{
    if(!active || !other->isActive())
        return;

    // TODO: This logic should probably live in the base class somehow
    if(auto* otherComp = dynamic_cast<CollisionComponent2DAABB*>(other))
    {
        glm::vec2 thisPosition = getWorldTransform().getPosition();
        glm::vec2 thisSize = this->size;
        glm::vec2 otherPosition = otherComp->getWorldTransform().getPosition();
        glm::vec2 otherSize = otherComp->getSize();

        bool xCollided = thisPosition.x + thisSize.x > otherPosition.x &&
                         otherPosition.x + otherSize.x > thisPosition.x;

        bool yCollided = thisPosition.y + thisSize.y > otherPosition.y &&
                         otherPosition.y + otherSize.y > thisPosition.y;

        if(xCollided && yCollided)
        {
            glm::vec3 start = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 end = glm::vec3(0.0f, 0.0f, 0.0f);

            if(thisPosition.x < otherPosition.x)
                start.x = otherPosition.x;
            else
                start.x = thisPosition.x;

            if(thisPosition.x + thisSize.x < otherPosition.x + otherSize.x)
                end.x = thisPosition.x + thisSize.x;
            else
                end.x = otherPosition.x + otherSize.x;

            if(thisPosition.y < otherPosition.y)
                start.y = otherPosition.y;
            else
                start.y = thisPosition.y;

            if(thisPosition.y + thisSize.y < otherPosition.y + otherSize.y)
                end.y = thisPosition.y + thisSize.y;
            else
                end.y = otherPosition.y + otherSize.y;

            glm::vec3 overlap = (end - start);
            (receiver->collisionCallback)(otherComp->getReceiver(), overlap);
            (otherComp->getReceiver()->collisionCallback)(receiver, -overlap);
        }
    }
    else if(auto* otherComp = dynamic_cast<CollisionComponent2DRound*>(other))
    {
        glm::vec2 thisPosition = getWorldTransform().getPosition();

        glm::vec2 thisHalfExtents(size.x/2, size.y/2);
        glm::vec2 thisCenter(thisPosition.x + thisHalfExtents.x,
                             thisPosition.y + thisHalfExtents.y);
        glm::vec2 otherCenter = otherComp->getCenterWorldTransform().getPosition();

        glm::vec2 difference = otherCenter - thisCenter;
        glm::vec2 clamped = glm::clamp(difference, -thisHalfExtents, thisHalfExtents);

        glm::vec2 closestPoint = thisCenter + clamped;

        difference = closestPoint - otherCenter;

        bool collided = glm::length(difference) < otherComp->getRadius();

        if(collided)
        {
            float differenceRatio = otherComp->getRadius()/glm::length(difference);
            glm::vec2 overlap = (difference * differenceRatio) - difference;

            (receiver->collisionCallback)(otherComp->getReceiver(), glm::vec3(-overlap.x, -overlap.y, 0.0f));
            (otherComp->getReceiver()->collisionCallback)(receiver, glm::vec3(overlap.x, overlap.y, 0.0f));
        }
    }
}
