#include "spriteComponent.h"
#include "entity.h"
#include "renderer.h"
#include "texture.h"

void SpriteComponent::Create(const std::string & textureName, const Vector2D& origin)
{
	m_texture = new Texture();
	m_origin = origin;
	m_texture->Create(textureName);
}

void SpriteComponent::Destroy()
{
	//
}

void SpriteComponent::Update()
{
	//
}

void SpriteComponent::Draw()
{

	Transform transform = m_owner->GetTransform();
	m_texture->Draw(transform.position, m_origin, transform.scale, transform.rotation);
	
}