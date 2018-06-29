#include "engine.h"
#include "textureManager.h"
#include <cassert>

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	m_renderer = SDL_CreateRenderer(m_window, -1, 0);

	m_textureManager = new TextureManager;
	m_textureManager->Initialize(this);

	return true;
}

void Engine::Shutdown()
{
	m_textureManager->Shutdown();

	SDL_DestroyRenderer(m_renderer);
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

	SDL_SetRenderDrawColor(m_renderer, 50, 50, 255, 255);
	SDL_RenderClear(m_renderer);

	SDL_Rect rect = { 300, 200, 64, 64 };
	SDL_Texture* texture = m_textureManager->GetTexture("..\\content\\crate.bmp");

	SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
	SDL_SetRenderDrawColor(m_renderer, 50, 50, 50, 255);
	//SDL_RenderFillRect(m_renderer, &rect);
	//SDL_RenderCopy(m_renderer, m_texture, nullptr, &rect);
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &rect, 45.0, nullptr, SDL_FLIP_NONE);
	

	SDL_RenderPresent(m_renderer);

}