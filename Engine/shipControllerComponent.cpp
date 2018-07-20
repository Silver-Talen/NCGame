#include "shipControllerComponent.h"
#include "transformComponent.h"
#include "inputManager.h"
#include "entity.h"
#include "timer.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
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
	
	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();
	transform->position.x += (force.x * m_speed) * Timer::Instance()->DeltaTime();
	
}