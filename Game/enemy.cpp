#include "enemy.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "enemyControllerComponent.h"
#include "waypointControllerComponent.h"
#include "transformControllerComponent.h"
#include "explosion.h"
#include "aabbComponent.h"
#include "renderer.h"
#include "timer.h"
#include "audioSystem.h"
#include "eventManager.h"
#include "animationComponent.h"
#include "formation.h"
#include "missile.h"

void Enemy::Create(const Info& info)
{
	m_info = info;

	SetTag("enemy");
	m_transform.position = Vector2D::zero;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string> animations;
	if (m_info.type == BOSS) animations = { "enemy01A.png", "enemy01B.png" };
	if (m_info.type == BEE) animations = { "enemy02A.png", "enemy02B.png" };
	if (m_info.type == BUG) animations = { "enemy03A.png", "enemy03B.png" };
	animationComponent->Create(animations, 5.0f / 10.0f, AnimationComponent::ePlayback::LOOP);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));
	
	/*SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));*/

	//EnemyTargetControllerComponent* enemyTargetControllerComponent = AddComponent<EnemyTargetControllerComponent>();
	//enemyTargetControllerComponent->Create(Vector2D(400.0f, 300.0f),200.0f);

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.7f, 0.9f));

	m_stateMachine = new StateMachine(GetScene(), this);
	m_stateMachine->AddState("enter_path", new EnterPathState(m_stateMachine));
	m_stateMachine->AddState("enter_formation", new EnterFormationState(m_stateMachine));
	m_stateMachine->AddState("idle", new IdleState(m_stateMachine));
	m_stateMachine->AddState("attack", new AttackState(m_stateMachine));
	m_stateMachine->SetState("enter_path");
}

void Enemy::Update()
{
	Entity::Update();

	m_stateMachine->Update();
}

void Enemy::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "playermissile")
		{
  			Event _event;
			_event.eventID = "add_score";
			_event.variants[0].asInteger = 100;
			_event.variants[0].type = Variant::INTEGER;
			EventManager::Instance()->SendGameMessage(_event);

			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position, Explosion::ENEMY);

			SetState(Entity::DESTROY);
		}
		
		if (event.sender->GetTag() == "player")
		{
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			explosion->Create(m_transform.position, Explosion::ENEMY);

			SetState(Entity::DESTROY);
		}
	}
}

void EnterPathState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_info.formation->GetEnterPath(m_owner->GetEntity<Enemy>()->m_info.side), m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f, true);
}

void EnterPathState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->SetState("enter_formation");
	}
}

void EnterPathState::Exit()
{
}

void EnterFormationState::Enter()
{
	WaypointControllerComponent* controller = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	controller->Create(std::vector<Vector2D> { m_owner->GetEntity<Enemy>()->m_info.target }, m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f);
}

void EnterFormationState::Update()
{
	WaypointControllerComponent* controller = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (controller && controller->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(controller);
		m_owner->SetState("idle");
	}
}

void EnterFormationState::Exit()
{
}

void IdleState::Enter()
{
	TransformControllerComponent* controller = m_owner->GetEntity()->AddComponent<TransformControllerComponent>();
	controller->Create(m_owner->GetEntity<Enemy>()->m_info.target, 180.0f, m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f);

	m_timer = Math::GetRandomRange(m_timeMin, m_timeMax);
	if (m_enter)
	{
		m_enter = false;
		m_timer += 30.0f;
	}
}

void IdleState::Update()
{
	float dt = Timer::Instance()->DeltaTime();
	m_timer -= dt;
	if (m_timer <= 0.0f)
	{
		TransformControllerComponent* controller = m_owner->GetEntity()->GetComponent<TransformControllerComponent>();
		m_owner->GetEntity()->RemoveComponent(controller);
		m_owner->SetState("attack");
	}
}

void IdleState::Exit()
{
	
}

void AttackState::Enter()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->AddComponent<WaypointControllerComponent>();
	waypointController->Create(m_owner->GetEntity<Enemy>()->m_info.formation->GetRandomAttackPath(), m_owner->GetEntity<Enemy>()->m_info.speed, 5.0f);
}

void AttackState::Update()
{
	WaypointControllerComponent* waypointController = m_owner->GetEntity()->GetComponent<WaypointControllerComponent>();
	if (waypointController && waypointController->IsComplete())
	{
		m_owner->GetEntity()->RemoveComponent(waypointController);
		m_owner->GetEntity()->GetTransform().position.y = -64.0f;
		m_owner->SetState("enter_formation");
	}

	std::vector<Entity*> missiles = m_owner->GetEntity<Enemy>()->GetScene()->GetEntitiesWithTag("enemyMissile");

	/*if (missiles.size() < 2)
	{
		Missile* missile = new Missile(m_owner->GetEntity<Enemy>()->GetScene());
		missile->Create("enemyMissile", m_owner->GetEntity<Enemy>()->GetTransform().position, Vector2D::up, 800.0f);
		m_owner->GetEntity<Enemy>()->GetScene()->AddEntity(missile);
		AudioSystem::Instance()->PlaySound("laser", false);
	}*/
}

void AttackState::Exit()
{
}