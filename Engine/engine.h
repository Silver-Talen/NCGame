#pragma once

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

#pragma warning(disable:4251)

#include "sdl.h"
#include <SDL_ttf.h>

class TextureManager;

class ENGINE_API Engine
{
public:
	Engine() {}
	~Engine() {}

	bool Initialize();
	void Update();
	void Shutdown();

	SDL_Window* GetWindow() { return m_window; }

	bool IsQuit() { return m_isQuit; }
	bool IsDebug() { return m_isDebug; }

protected:
	bool m_isQuit = false;
	bool m_isDebug = true;
	SDL_Window * m_window = nullptr;
};