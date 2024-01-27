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
    std::vector<std::unique_ptr<Entity>> children;
	std::vector<std::unique_ptr<Component>> components;
	Transform transform;
    Scene* owningScene;

public:
	bool receivesUpdates = false;
    bool shouldBeDestroyed = false;

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

    template <typename T, typename... Args>
    T* addChild(Args... args)
    {
        children.push_back(std::make_unique<T>(args...));
        children.back()->setOwningScene(owningScene);

        return dynamic_cast<T*>(children.back().get());
    }

    template <typename T, typename... Args>
    T* addComponent(Args... args)
    {
        T* component = new T(args...);
        components.push_back(std::unique_ptr<T>(component));
        components.back()->setParent(this);

       return component;
    }

	Transform* getTransform() { return &transform; }
	Transform getWorldTransform();
};

#endif
