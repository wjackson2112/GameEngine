#include "Entity.h"
#include "GraphicsComponent.h"
#include "ModelComponent.h"
#include "Mesh.h"

#include <algorithm>

void Entity::setParent(Entity* entity)
{
	parent = entity;
}

void Entity::setOwningScene(Scene *scene)
{
    owningScene = scene;
}

Transform Entity::getWorldTransform()
{
	if(parent)
		return parent->getWorldTransform().compose(transform);
	else
		return transform;
}

void Entity::draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos)
{
    for(const auto& component : components)
        component->draw(view, projection, lightDir, viewPos);
}

void Entity::earlyUpdate(float deltaTime)
{
    for(const auto& component : components)
        if(component->shouldUpdate)
            component->earlyUpdate(deltaTime);
}

void Entity::update(float deltaTime)
{
    for(const auto& component : components)
        if(component->shouldUpdate)
            component->update(deltaTime);
}

void Entity::lateUpdate(float deltaTime)
{
    for(const auto& component : components)
        if(component->shouldUpdate)
            component->lateUpdate(deltaTime);
}