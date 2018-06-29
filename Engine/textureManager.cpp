#include "textureManager.h"
#include <cassert>

bool TextureManager::Initialize(Engine * engine)
{
	m_engine = engine;

	return true;
}

void TextureManager::Shutdown()
{
	for (auto texture : m_textures)
	{
		SDL_DestroyTexture(texture.second);
	}
}

SDL_Texture * TextureManager::GetTexture(const std::string & textureName)
{
	SDL_Texture* texture = m_textures[textureName];

	if (!texture)
	{
		SDL_Surface* surface = SDL_LoadBMP(textureName.c_str());
		assert(surface);
		texture = SDL_CreateTextureFromSurface(m_engine->GetRenderer(), surface);
		SDL_FreeSurface(surface);

		m_textures[textureName] = texture;
	}
	
	return texture;
}
