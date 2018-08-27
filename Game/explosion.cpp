#include "explosion.h"
#include "spriteComponent.h"
#include "animationComponent.h"
#include "audioSystem.h"


void Explosion::Create(const Vector2D & position, eType type)
{
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);
	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("", Vector2D(0.5f, 0.5f));

	AudioSystem::Instance()->AddSound("enemyExplosion", "enemy-hit01.wav");
	AudioSystem::Instance()->AddSound("playerExplosion", "ship-explosion.wav");

	std::vector<std::string> textureNames;
	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	switch (type)
	{
	case ENEMY:
		textureNames = { "enemy-explosion01.png", "enemy-explosion02.png", "enemy-explosion03.png", "enemy-explosion04.png", "enemy-explosion05.png" };
		AudioSystem::Instance()->PlaySound("enemyExplosion");
		break;
	case PLAYER:
		textureNames = { "ship-explosion01.png", "ship-explosion02.png", "ship-explosion03.png", "ship-explosion04.png" };
		AudioSystem::Instance()->PlaySound("playerExplosion");
		break;
	}
	animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayback::ONE_TIME_DESTROY);
}

void Explosion::Update()
{
	Entity::Update();
}
