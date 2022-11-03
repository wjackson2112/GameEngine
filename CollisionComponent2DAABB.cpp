//
// Created by Will on 7/1/2022.
//

#include "CollisionComponent2DAABB.h"
#include "CollisionComponent2DRound.h"

void CollisionComponent2DAABB::resolveIfCollided(CollisionComponentBase* other)
{
    // TODO: This logic should probably live in the base class somehow
    if(auto* otherComp = dynamic_cast<CollisionComponent2DAABB*>(other))
    {
        glm::vec2 thisPosition = parent->getWorldTransform().getPosition();
        glm::vec2 otherPosition = otherComp->parent->getWorldTransform().getPosition();

        bool xCollided = thisPosition.x + this->size.x > otherPosition.x &&
                         otherPosition.x + otherComp->getSize().x > thisPosition.x;

        bool yCollided = thisPosition.y + this->size.y > otherPosition.y &&
                         otherPosition.y + otherComp->getSize().y > thisPosition.y;

        if(xCollided && yCollided)
        {
            glm::vec3 overlap = glm::vec3(0.0f, 0.0f, 0.0f); // TODO: Make this a real vector representing the overlap

            (receiver->collisionCallback)(otherComp->getReceiver(), overlap);
            (otherComp->getReceiver()->collisionCallback)(receiver, -overlap);
        }
    }
    else if(auto* otherComp = dynamic_cast<CollisionComponent2DRound*>(other))
    {
        glm::vec2 thisPosition = parent->getWorldTransform().getPosition();

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
