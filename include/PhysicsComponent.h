#ifndef PHYSICS_COMPONENT_H
#define PHYSICS_COMPONENT_H

#include "Component.h"


class PhysicsComponent : public Component
{
public:
    // Component Interface
    void update(float deltaTime) override {};
    // End Component Interface
};

#endif //PHYSICS_COMPONENT_H