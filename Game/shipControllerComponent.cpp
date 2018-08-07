#include "shipControllerComponent.h"
#include "kinematicComponent.h"
#include "audioSystem.h"
#include "transform.h"
#include "inputManager.h"
#include "entity.h"
#include "ship.h"
#include "missile.h"
#include "timer.h"
#include <iostream>

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);

	AudioSystem::Instance()->AddSound("laser", "laser.wav");
}

void ShipControllerComponent::Destroy()
{

}

void ShipControllerComponent::Update()
{
	Vector2D force = Vector2D::zero;
	if (InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED ||
		InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD)
	{
		force.x -= 1.0f;
	}

	if (InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED ||
		InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD)
	{
		force.x += 1.0f;
	}

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		std::vector<Entity*> missiles = m_owner->GetScene()->GetEntitiesWithTag("playermissile");

		if (missiles.size() < 2)
		{
		Missile* missile = new Missile(m_owner->GetScene());
		missile->Create("playermissile", m_owner->GetTransform().position, Vector2D::down, 800.0f);
		m_owner->GetScene()->AddEntity(missile);
		AudioSystem::Instance()->PlaySound("laser", false);
		}

		std::cout << "pew" << std::endl;
	}
}