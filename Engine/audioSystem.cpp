#include "audioSystem.h"
#include <assert.h>

bool AudioSystem::Initialize(Engine * engine)
{
	m_engine = engine;

	FMOD_RESULT result = FMOD::System_Create(&m_fmodSystem);
	assert(result == FMOD_OK);

	void* extradriverdata = nullptr;
	result = m_fmodSystem->init(32, FMOD_INIT_NORMAL, extradriverdata);
	assert(result == FMOD_OK);

	return true;
}

void AudioSystem::Shutdown()
{
	for (auto sound : m_sounds)
	{
		 sound.second->release();
	}
	m_sounds.clear();
	m_fmodSystem->close();
	m_fmodSystem->release();
}

void AudioSystem::AddSound(const std::string & id, const std::string & filename)
{

}

void AudioSystem::PlaySound(const std::string & id)
{

}

void AudioSystem::RemoveSound(const std::string & id)
{

}