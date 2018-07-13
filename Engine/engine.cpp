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
	m_window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);

	Timer::Instance()->Initialize(this);
	Renderer::Instance()->Initialize(this);
	TextureManager::Instance()->Initialize(this);
	TextManager::Instance()->Initialize(this);
	InputManager::Instance()->Initialize(this);
	AudioSystem::Instance()->Initialize(this);

	//Sounds
	AudioSystem::Instance()->AddSound("horn", "..\\content\\horn.wav");
	AudioSystem::Instance()->AddSound("laser", "..\\content\\laser.wav");

	//Mouse Actions
	InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);
	InputManager::Instance()->AddAction("steer", InputManager::eAxis::X, InputManager::eDevice::MOUSE);

	//Keyboard Actions
	InputManager::Instance()->AddAction("horn", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("up", SDL_SCANCODE_UP, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("down", SDL_SCANCODE_DOWN, InputManager::eDevice::KEYBOARD);
	
	text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Inconsolata-Bold.ttf", 24, Color::red);
	
	return true;
}

void Engine::Shutdown()
{
	Timer::Instance()->Shutdown();
	Renderer::Instance()->Shutdown();
	TextureManager::Instance()->Shutdown();
	TextManager::Instance()->Shutdown();
	InputManager::Instance()->Shutdown();
	AudioSystem::Instance()->Shutdown();

	SDL_DestroyWindow(m_window);
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

	//Test
	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		std::cout << "pew\n";
	}

	//Pause
	if (InputManager::Instance()->GetButtonState(SDL_SCANCODE_RETURN) == InputManager::eButtonState::PRESSED)
	{
		(Timer::Instance()->IsPaused()) ? Timer::Instance()->Unpause() : Timer::Instance()->Pause(); 
	}

	//Movement
	if (InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED ||
		InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD)
	{
		angle -= 180.0f * Timer::Instance()->DeltaTime();
	}

	if (InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED ||
		InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD)
	{
		angle += 180.0f * Timer::Instance()->DeltaTime();
	}

	float steer = InputManager::Instance()->GetActionRelative("steer");
	angle += (steer * 200.0f) * Timer::Instance()->DeltaTime();

	Vector2D force = Vector2D::zero;
	if (InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::PRESSED ||
		InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD)
	{
		force.y = -300.0f * Timer::Instance()->DeltaTime();
	}

	if (InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::PRESSED ||
		InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD)
	{
		force.y = 300.0f * Timer::Instance()->DeltaTime();
	}

	//Sound
	if (InputManager::Instance()->GetActionButton("horn") == InputManager::eButtonState::PRESSED)
	{
		std::cout << "beep\n";
		AudioSystem::Instance()->PlaySound("horn", false);
	}
	if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	{
		AudioSystem::Instance()->PlaySound("laser", false);
	}

	Matrix22 mx;
	mx.Rotate(angle * Math::DegreesToRadians);
	force = force * mx;
	position += force;

	//DRAW
	Renderer::Instance()->BeginFrome();
	Renderer::Instance()->SetColor(Color::black);

	float xy = InputManager::Instance()->GetActionRelative("steer");
	std::string str = std::to_string(x);


	std::vector<Color> colors = { Color::red, Color::green, Color::white };
	//text->SetText("Hello World", colors[rand() % colors.size()]);
	text->SetText(str, colors[rand() % colors.size()]);
	text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");
	Renderer::Instance()->DrawTexture(texture, position, angle);
	//Renderer::Instance()->DrawTexture(texture, position, scalar, 0.0f);

	Renderer::Instance()->EndFrame();
}