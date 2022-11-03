#include "Entity.h"
#include "GraphicsComponent.h"
#include "ModelComponent.h"
#include "Mesh.h"

Entity::~Entity()
{
	for(Entity* child : children)
		delete child;

	for(Component* component : components) 
		delete component;
}

void Entity::addChild(Entity* child)
{
	child->setParent(this);
	children.push_back(child);
}

void Entity::setParent(Entity* entity)
{
	parent = entity;
}

void Entity::addComponent(Component* component)
{
	component->setParent(this);
	components.push_back(component);
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
    for(Component* component : components)
        component->draw(view, projection, lightDir, viewPos);

	for(Entity* child : children)
		child->draw(view, projection, lightDir, viewPos);
}

void Entity::update(float deltaTime)
{
    for(Component* component : components)
        if(component->receivesUpdates)
            component->update(deltaTime);

    for(Entity* child : children)
        if(child->receivesUpdates)
            child->update(deltaTime);
}