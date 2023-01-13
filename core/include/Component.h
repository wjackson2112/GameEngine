#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>

#include "Transform.h"

class Entity;

class Component 
{
protected:
    Entity* parent = nullptr;
    Transform transform = Transform(glm::vec3(0.f, 0.f, 0.f));

public:
    bool receivesUpdates = false;
    // TODO: This should probably be updated to enforce that all components have a parent set
    Component() : parent(nullptr) { }

    virtual void update(float deltaTime) {};
    virtual void lateUpdate(float deltaTime) {};
    virtual void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos) {};
    void setParent(Entity* in_parent);
    void setTransform(Transform transform);
    Transform getWorldTransform();
};

#endif //COMPONENT_H