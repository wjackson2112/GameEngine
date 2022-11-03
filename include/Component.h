#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm/glm.hpp>

class Entity;

class Component 
{
protected:
    Entity* parent;

public:
    bool receivesUpdates = false;
    // TODO: This should probably be updated to enforce that all components have a parent set
    Component() : parent(nullptr) { }

    virtual void update(float deltaTime) {};
    virtual void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos) {};
    void setParent(Entity* in_parent)
    {
        this->parent = in_parent;
    }
};

#endif //COMPONENT_H