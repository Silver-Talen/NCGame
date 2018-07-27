#include "scene.h"
#include "entity.h"
#include <assert.h>

bool Scene::Initialize()
{
	return true;
}

void Scene::Shutdown()
{
	for (Entity* entity : m_entities)
	{
		delete entity;
	}
	m_entities.clear();
}

void Scene::Update()
{
	size_t size = m_entities.size();
	for (size_t i = 0; i < size; i++)
	{
		m_entities[i]->Update();
	}
}

void Scene::Draw()
{
	for (Entity* entity : m_entities)
	{
		entity->Draw();
	}
}

void Scene::AddEntity(Entity * entity)
{
	assert(entity);
	assert(std::find(m_entities.begin(), m_entities.end(), entity) == m_entities.end());
	m_entities.push_back(entity);
}

void Scene::RemoveEntity(Entity * entity)
{
	assert(entity);
	assert(std::find(m_entities.begin(), m_entities.end(), entity) != m_entities.end());

	auto iter = std::find(m_entities.begin(), m_entities.end(), entity);
	if (iter != m_entities.end())
	{
		m_entities.erase(iter);
	}
}

Entity * Scene::FindEntity(const ID & id)
{
	Entity* entity = nullptr;
	for (Entity* _entity : m_entities)
	{
		if (*_entity == id)
		{
			entity = _entity;
			break;
		}
	}
	return entity;
}