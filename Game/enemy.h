#pragma once
#include "entity.h"
#include "vector2D.h"

class Enemy : public Entity
{
public:
	Enemy(Scene* scene) : Entity(scene) {}
	~Enemy() {}

	void Create(const Vector2D& position, float movementTimer);
	void Update();
	void Destroy();

private:
	Vector2D m_force = Vector2D::zero;
	float m_speed;
	float m_movementTimer;
};