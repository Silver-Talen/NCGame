#include "states.h"
#include "entity.h"
#include "spriteComponent.h"
#include "stateMachine.h"
#include "inputManager.h"
#include "enemy.h"
#include "ship.h"
#include "renderer.h"

void TitleState::Enter()
{
	Entity* entity = m_owner->GetScene()->AddEntity<Entity>("title");
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = entity->AddComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);

	InputManager::Instance()->AddAction("start", SDL_SCANCODE_RETURN, InputManager::eDevice::KEYBOARD);
	
	m_credits = 0;
}

void TitleState::Update()
{
	if (InputManager::Instance()->GetActionButton("start") == InputManager::eButtonState::PRESSED)
	{
		m_owner->SetState("game");
	}
}

void TitleState::Exit()
{
	Entity* entity = m_owner->GetScene()->GetEntityWithID("title");
	if (entity)
	{
		entity->SetState(Entity::DESTROY);
	}
}

void GameState::Enter()
{
	Ship* ship = new Ship(m_owner->GetScene(), "player");
	ship->Create(Vector2D(400.0f, 550.0f));
	m_owner->GetScene()->AddEntity(ship);

	for (size_t i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy(m_owner->GetScene());
		float x = Math::GetRandomRange(25.0f, Renderer::Instance()->GetSize().x - 25.0f);
		float y = Math::GetRandomRange(-225.0f, -Renderer::Instance()->GetSize().y);
		enemy->Create(Vector2D(x, y), 3.0f);
		m_owner->GetScene()->AddEntity(enemy);
	}
}

void GameState::Update()
{

}

void GameState::Exit()
{

}