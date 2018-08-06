#include "entity.h"
#include "renderComponent.h"
#include <assert.h>
#include <algorithm>

void Entity::Update()
{
	for (Component* component : m_components)
	{
		component->Update();
	}
}

void Entity::Draw()
{
	IRenderComponent* renderComponent = GetComponent<IRenderComponent>();
	if (renderComponent)
	{
		renderComponent->Draw();
	}
}

void Entity::Destroy()
{
	for (Component* component : m_components)
	{
		component->Destroy();
		delete component;
	}
	m_components.clear();
}

void Entity::OnEvent(const Event & event)
{
}

void Entity::AddComponent(Component * component)
{
	assert(component);
	assert(std::find(m_components.begin(), m_components.end(), component) == m_components.end());

	m_components.push_back(component);
}

void Entity::RemoveComponent(Component * component)
{
	assert(std::find(m_components.begin(), m_components.end(), component) != m_components.end());

	std::vector<Component*>::iterator iter = std::find(m_components.begin(), m_components.end(), component);
	if (iter != m_components.end())
	{
		delete * iter;
		m_components.erase(iter);
	}
}