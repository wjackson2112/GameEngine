#ifndef ENTITY_H
#define ENTITY_H

#include <vector>

#include <glm/glm.hpp>

#include "Shader.h"
#include "Component.h"
#include "Transform.h"

class Scene;

class Entity
{
protected:
	Entity* parent = nullptr;
	std::vector<Entity*> children;
	std::vector<Component*> components;
	Transform transform;
    Scene* owningScene;

public:
	bool receivesUpdates = false;
    bool shouldBeDestroyed = false;

    // Entity(){};
	// Entity(const Entity &other);
	virtual ~Entity();
	
	void addChild(Entity* child);
    void removeChild(Entity* child);
	void setParent(Entity* parent);
    void setOwningScene(Scene* scene);
	void addComponent(Component* component);

	void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos);
	virtual void earlyUpdate(float deltaTime);
    virtual void update(float deltaTime);
    virtual void lateUpdate(float deltaTime);

	template <class T>
	T* getComponent()
	{
		for(Component* c : components)
		{
			if(T* component = dynamic_cast<T*>(c))
			{
				return component;
			}
		}
		return nullptr;
	}

    template <class T>
    std::vector<T*> getComponents()
    {
        std::vector<T*> returnValue;
        for(Component* c : components)
        {
            if(T* component = dynamic_cast<T*>(c))
            {
                returnValue.push_back(component);
            }
        }
        return returnValue;
    }

	Transform* getTransform() { return &transform; }
	Transform getWorldTransform();
};

#endif
