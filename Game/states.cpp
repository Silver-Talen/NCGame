#include "states.h"
#include "entity.h"
#include "stateMachine.h"
#include "spriteComponent.h"
#include "inputManager.h"
#include "formation.h"
#include "enemy.h"
#include "timer.h"
#include "ship.h"

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
	if (InputManager::Instance()->GetActionButton("start"))
	{
		m_owner->SetState("enter_stage");
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

void EnterStageState::Enter()
{
	Timer::Instance()->Reset();
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntityWithID("formation"));
	if (formation == nullptr)
	{
		formation = m_owner->GetScene()->AddEntity<Formation>("formation");
		formation->Create();
	}
}

void EnterStageState::Update()
{
	Formation* formation = dynamic_cast<Formation*>(m_owner->GetScene()->GetEntityWithID("formation"));
	formation->Update();

	Ship* ship = new Ship(m_owner->GetScene(), "player");
	ship->Create(Vector2D(400.0f, 500.0f));
	m_owner->GetScene()->AddEntity(ship);

	m_owner->SetState("game");
}

void EnterStageState::Exit()
{
	
}

void GameState::Enter()
{
	
}	

void GameState::Update()
{
	if (!m_owner->GetScene()->GetEntityWithID("player"))
	{
		Ship* ship = new Ship(m_owner->GetScene(), "player");
		ship->Create(Vector2D(400.0f, 500.0f));
		m_owner->GetScene()->AddEntity(ship);
	}
}

void GameState::Exit()
{

}