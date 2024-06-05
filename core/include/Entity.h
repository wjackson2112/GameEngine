#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <memory>

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
	std::vector<std::unique_ptr<Component>> components;
	Transform transform;
    Scene* owningScene;

public:
	bool shouldUpdate = false;
    bool shouldDraw = true;
    bool shouldBeDestroyed = false;

    virtual ~Entity() = default;

	void setParent(Entity* parent);
    void setOwningScene(Scene* scene);

	void draw(glm::mat4 view, glm::mat4 projection, glm::vec3 lightDir, glm::vec3 viewPos);
	virtual void earlyUpdate(float deltaTime);
    virtual void update(float deltaTime);
    virtual void lateUpdate(float deltaTime);

	template <class T>
	T* getComponent()
	{
		for(const auto& c : components)
		{
			if(T* component = dynamic_cast<T*>(c.get()))
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
        for(const auto& c : components)
        {
            if(T* component = dynamic_cast<T*>(c.get()))
            {
                returnValue.push_back(component);
            }
        }
        return returnValue;
    }

    template <typename T>
    void addChild(T* child)
    {
        children.push_back(child);
        children.back()->setParent(this);
    }

    void removeChild(Entity* in_child)
    {
        for(unsigned int i = 0; i < children.size(); i++)
        {
            if(in_child == children[i])
            {
                children[i]->setParent(nullptr);
                children.erase(children.begin() + i);
                break;
            }
        }
    }

    template <typename T>
    void addComponent(T* component)
    {
        components.push_back(std::unique_ptr<T>(component));
        components.back()->setParent(this);
    }

	Transform* getTransform() { return &transform; }
	Transform getWorldTransform();
};

#endif
