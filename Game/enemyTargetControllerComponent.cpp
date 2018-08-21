#include "enemyTargetControllerComponent.h"
#include "kinematicComponent.h"
#include "audioSystem.h"
#include "transform.h"
#include "inputManager.h"
#include "entity.h"
#include "ship.h"
#include "missile.h"
#include "timer.h"
#include "debugDraw.h"

void EnemyTargetControllerComponent::Create(const Vector2D& target, float speed)
{
	m_speed = speed;
	m_target = target;
}

void EnemyTargetControllerComponent::Destroy()
{

}

void EnemyTargetControllerComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();

	Vector2D direction = m_target - m_owner->GetTransform().position;
	float rotation = (Vector2D::GetAngle(direction) * Math::RadiansToDegrees + 90.0f);
	m_owner->GetTransform().rotation = Math::LerpDegrees(m_owner->GetTransform().rotation, rotation, 1.0f * dt);

	Vector2D force = Vector2D::Rotate(Vector2D::down, m_owner->GetTransform().rotation * Math::DegreesToRadians + Math::PI);
	DEBUG_DRAW_LINE(m_owner->GetTransform().position, m_owner->GetTransform().position + force * 60.0f, Color::blue)

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	DEBUG_DRAW_CROSS(m_target, Vector2D(20.0f, 20.0f), Color::white)
}