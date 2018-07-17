#include "entity.h"
#include <algorithm>

void Entity::AddComponent(Component * component)
{
	m_components.push_back(component);
}

void Entity::RemoveComponent(Component * component)
{
	std::vector<Component*>::iterator iter = std::find(m_components.begin(), m_components.end(), component);
	if (iter != m_components.end())
	{
		delete * iter;
		m_components.erase(iter);
	}
}