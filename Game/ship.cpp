#include "ship.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "shipControllerComponent.h"
#include "explosion.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "eventManager.h"

void Ship::Create(const Vector2D & position)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SetTag("player");

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 0.5f));

	ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	shipControllerComponent->Create(600.0f);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();
}

void Ship::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
}


void Ship::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy")
		{
			SetState(Entity::DESTROY);
		}
	}
	
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemymissile")
		{
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTROY);
		}
	}
}