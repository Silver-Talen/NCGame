#include "engine.h"
#include "textManager.h"
#include "textureManager.h"
#include "renderer.h"
#include "audioSystem.h"
#include "physics.h"
#include "inputManager.h"
#include "timer.h"
#include "fileSystem.h"

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	FileSystem::Instance()->Initialize(this);
	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	TextManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);
	Physics::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	
	return true;
}

void Engine::Shutdown()
{
	Timer::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	TextManager::Instance()->Shutdown();
	AudioSystem::Instance()->Shutdown();
	Physics::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	FileSystem::Instance()->Shutdown();

	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	//Timer::Instance()->SetTimeScale(5.0f);
	Physics::Instance()->Update();
	InputManager::Instance()->Update();
	AudioSystem::Instance()->Update();
	FileSystem::Instance()->Update();

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}
	}
}