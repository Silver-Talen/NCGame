#pragma once

#include "object.h"
#include "component.h"
#include "transform.h"
#include "scene.h"
#include "event.h"
#include <vector>
#include <assert.h>

class ENGINE_API Entity : public Object
{
public:
	enum eState
	{
		INACTIVE,
		ACTIVE,
		DESTROY
	};

public:
	Entity(Scene* scene, const ID& id = ID()) : m_scene(scene), Object(id) {}
	virtual ~Entity() {}

	virtual void Update();
	virtual void Draw();
	virtual void Destroy();

	virtual void OnEvent(const Event& event);

	Scene* GetScene() { return m_scene; }
	Transform& GetTransform() { return m_transform; }

	void SetState(eState state) { m_state = state; }
	eState GetState() { return m_state; }

	void SetTag(const ID& tag) { m_tag = tag; }
	ID GetTag() { return m_tag; }

	template <typename T>
	T* AddComponent()
	{
		T* component = new T(this);
		assert(dynamic_cast<Component*>(component));
		m_components.push_back(component);

		return component;
	}

	void AddComponent(Component* component);
	void RemoveComponent(Component* component);

	template <typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* _component : m_components)
		{
			component = dynamic_cast<T*>(_component);
			if (component != nullptr) break;
		}
		return component;
	}

	

protected:
	Transform m_transform;
	ID m_tag;
	std::vector<Component*> m_components;
	Scene * m_scene;
	eState m_state = ACTIVE;
};