#pragma once
#include "singleton.h"
#include "engine.h"

class AudioSystem : public Singleton<AudioSystem>
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();

protected:
	AudioSystem() {}
	~AudioSystem() {}

private:
	Engine * m_engine;
};