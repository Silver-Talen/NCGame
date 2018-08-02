#include "enemyControllerComponent.h"
#include "kinematicComponent.h"
#include "audioSystem.h"
#include "transform.h"
#include "inputManager.h"
#include "entity.h"
#include "ship.h"
#include "missile.h"
#include "timer.h"
#include <iostream>

void EnemyControllerComponent::Create(float speed)
{
	m_speed = speed;
}

void EnemyControllerComponent::Destroy()
{

}

void EnemyControllerComponent::Update()
{
	Vector2D force = Vector2D::up;

	Entity* player = m_owner->GetScene()->FindEntity("player");
	if (player)
	{
		float dx = player->GetTransform().position.x - m_owner->GetTransform().position.x;
		if (dx < -32.0f) force.x = -0.7f;
		if (dx > 32.0f) force.x = 0.7f;
	}
	
	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}
}