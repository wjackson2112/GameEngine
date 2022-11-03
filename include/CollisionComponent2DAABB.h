//
// Created by Will on 7/1/2022.
//

#ifndef COLLISION_COMPONENT_2D_AABB_H
#define COLLISION_COMPONENT_2D_AABB_H

#include "CollisionComponentBase.h"

class CollisionComponent2DAABB : public CollisionComponentBase
{
    glm::vec2 size = glm::vec2(0.0f, 0.0f);

public:
    CollisionComponent2DAABB(ICollisionReceiver* receiver, glm::vec2 size)
    : size(size)
    , CollisionComponentBase(receiver)
    { }

    inline glm::vec2 getSize() { return size; }
    inline void setSize(glm::vec2 in_size) { size = in_size; }

    // Start CollisionComponentBase
    void resolveIfCollided(CollisionComponentBase* other);
    // End CollisionComponentBase
};

#endif //COLLISION_COMPONENT_2D_AABB_H
