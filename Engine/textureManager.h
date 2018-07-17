#pragma once
#include "singleton.h"
#include "engine.h"
#include <map>

class ENGINE_API TextureManager : public Singleton<TextureManager>
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();

	friend Singleton<TextureManager>;

	SDL_Texture* GetTexture(const std::string& textureName);

protected:
	TextureManager() {}
	~TextureManager() {}

private:
	Engine * m_engine;
	std::map<std::string, SDL_Texture*> m_textures;
};