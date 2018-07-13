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

void AudioSystem::Update()
{
	m_fmodSystem->update();
}

void AudioSystem::AddSound(const std::string & id, const std::string & filename)
{
	assert(m_sounds.find(id) == m_sounds.end());

	FMOD::Sound* sound = nullptr;

	FMOD_RESULT result =  m_fmodSystem->createSound(filename.c_str(), FMOD_DEFAULT, 0, &sound);
	if (result == FMOD_OK)
	{
		m_sounds[id] = sound;
	}
}

void AudioSystem::PlaySound(const std::string & id, bool loop)
{
	assert(m_sounds.find(id) != m_sounds.end());

	FMOD::Channel* channel;
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* sound = iter->second;
		FMOD_MODE mode = (loop) ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
		sound->setMode(mode);
		FMOD_RESULT result = m_fmodSystem->playSound(m_sounds[id], 0, false, &channel);
		assert(result == FMOD_OK);
	}

}

void AudioSystem::RemoveSound(const std::string & id)
{
	assert(m_sounds.find(id) != m_sounds.end());
	auto iter = m_sounds.find(id);
	if (iter != m_sounds.end())
	{
		FMOD::Sound* sound = iter->second;
		FMOD_RESULT result = sound->release();
		assert(result == FMOD_OK);
		m_sounds[id]->release();
	}
}