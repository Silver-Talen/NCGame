#include "engine.h"
#include "text.h"
#include "textManager.h"
#include "textureManager.h"
#include "renderer.h"
#include "audioSystem.h"
#include "inputManager.h"
#include "timer.h"
#include "matrix22.h"
#include <assert.h>
#include <iostream>

Vector2D position(400.0f, 300.0f);
//Vector2D scalar(5.0f, 5.0f);
float angle = 0.0f;
Text* text;

bool Engine::Initialize()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);
	
	text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Inconsolata-Bold.ttf", 24, Color::red);
	
	return true;
}

void Engine::Shutdown()
{
	Timer::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	AudioSystem::Instance()->Shutdown();

	SDL_DestroyWindow(m_window);
	TTF_Quit();
	SDL_Quit();
}

void Engine::Update()
{
	Timer::Instance()->Update();
	//Timer::Instance()->SetTimeScale(5.0f);
	InputManager::Instance()->Update();

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

	if (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_RETURN) == InputManager::eAction::PRESSED)
	{
		(Timer::Instance()->IsPaused()) ? Timer::Instance()->Unpause() : Timer::Instance()->Pause(); 
	}

	if (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_LEFT) == InputManager::eAction::PRESSED || 
		InputManager::Instance()->GetButtonAction(SDL_SCANCODE_LEFT) == InputManager::eAction::HELD)
	{
		angle -= 180.0f * Timer::Instance()->DeltaTime();
	}

	if (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_RIGHT) == InputManager::eAction::PRESSED ||
		InputManager::Instance()->GetButtonAction(SDL_SCANCODE_RIGHT) == InputManager::eAction::HELD)
	{
		angle += 180.0f * Timer::Instance()->DeltaTime();
	}

	Vector2D force = Vector2D::zero;
	if (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_UP) == InputManager::eAction::PRESSED ||
		InputManager::Instance()->GetButtonAction(SDL_SCANCODE_UP) == InputManager::eAction::HELD)
	{
		force.y = -300.0f * Timer::Instance()->DeltaTime();
	}

	if (InputManager::Instance()->GetButtonAction(SDL_SCANCODE_DOWN) == InputManager::eAction::PRESSED ||
		InputManager::Instance()->GetButtonAction(SDL_SCANCODE_DOWN) == InputManager::eAction::HELD)
	{
		force.y = 300.0f * Timer::Instance()->DeltaTime();
	}

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position += force;

	Renderer::Instance()->BeginFrome();
	Renderer::Instance()->SetColor(Color::black);

	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	text->SetText("Hello World", colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	//DRAW
	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture, position, angle);
	//Renderer::Instance()->DrawTexture(texture, position, scalar, 0.0f);

	Renderer::Instance()->EndFrame();
}