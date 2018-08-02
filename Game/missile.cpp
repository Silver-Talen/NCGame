#include "missile.h"
#include "transform.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "timer.h"

void Missile::Create(const Vector2D & position, const Vector2D& direction, float speed)
{
	m_lifetime = 2.0f;
	SetTag("playermissile");

	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.9f);
	kinematic->ApplyForce((direction * speed), KinematicComponent::FORCE);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("missile01.png", Vector2D(0.5f, 0.5f));
}

void Missile::Update()
{
	Entity::Update();
	m_lifetime -= Timer::Instance()->DeltaTime();
	if (m_lifetime <= 0.0f)
	{
		SetState(Entity::DESTROY);
	}
}