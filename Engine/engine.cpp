#include "engine.h"
#include "textureManager.h"
#include "renderer.h"
#include "audioSystem.h"
#include "inputManager.h"
#include <cassert>

Vector2D position(0.0f, 0.0f);

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);

	return true;
}

void Engine::Shutdown()
{
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	AudioSystem::Instance()->Shutdown();

	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Engine::Update()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_isQuit = true;
		break;
	case SDL_KEYDOWN:
		if(event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_isQuit = true;
		}
	}

	int x, y;
	SDL_GetMouseState(&x, &y);

	const Uint8* keystate = SDL_GetKeyboardState(nullptr);
	if (keystate[SDL_SCANCODE_LEFT]) position.x -= 0.25f;
	if (keystate[SDL_SCANCODE_RIGHT]) position.x += 0.25f;
	if (keystate[SDL_SCANCODE_UP]) position.y -= 0.25f;
	if (keystate[SDL_SCANCODE_DOWN]) position.y += 0.25f;

	Renderer::Instance()->BeginFrome();

	Renderer::Instance()->SetColor(Color::blue);
	//DRAW
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\link.bmp");

	Renderer::Instance()->DrawTexture(texture, position, 0.0f);

	Renderer::Instance()->EndFrame();
}