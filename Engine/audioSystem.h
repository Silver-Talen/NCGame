#pragma once
#include "singleton.h"
#include "engine.h"
#include <string>
#include <map>
#include <fmod.hpp>

class AudioSystem : public Singleton<AudioSystem>
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();

	void AddSound(const std::string& id, const std::string& filename); 
	void PlaySound(const std::string& id); 
	void RemoveSound(const std::string& id);

public:
	AudioSystem() {}
	~AudioSystem() {}

private:
	Engine * m_engine;
	FMOD::System* m_fmodSystem;
	std::map<std::string, FMOD::Sound*> m_sounds;
};