#include "ship.h"
#include "transformComponent.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "shipControllerComponent.h"

void Ship::Create(const Vector2D & position)
{
	TransformComponent* transformComponent = AddComponent<TransformComponent>();
	transformComponent->Create(Vector2D(position));

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("..\\content\\ship.png");

	ShipControllerComponent* shipControllerComponent = AddComponent<ShipControllerComponent>();
	shipControllerComponent->Create(500.0f);
}