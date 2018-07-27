#include "game.h"
#include "engine.h"
#include "scene.h"
#include "textManager.h"
#include "textureManager.h"
#include "renderer.h"
#include "audioSystem.h"
#include "inputManager.h"
#include "entity.h"
#include "ship.h"

//Vector2D position(400.0f, 300.0f);
//Vector2D scalar(5.0f, 5.0f);
//float angle = 0.0f;
//Text* text;
bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	m_scene = new Scene();

	//for (size_t i = 0; i < 20; i++)
	//{
		Ship* ship = new Ship(m_scene);
		/*float x = (float)(rand() % 800);
		float y = (float)(rand() % 600);
		ship->Create(Vector2D(x, y));*/
		ship->Create(Vector2D(750.0f, 500.0f));

		m_scene->AddEntity(ship);
	//}

	////Sounds
	//AudioSystem::Instance()->AddSound("horn", "..\\content\\horn.wav");
	//AudioSystem::Instance()->AddSound("laser", "..\\content\\laser.wav");

	////Mouse Actions
	//InputManager::Instance()->AddAction("fire", SDL_BUTTON_LEFT, InputManager::eDevice::MOUSE);
	//InputManager::Instance()->AddAction("steer", InputManager::eAxis::X, InputManager::eDevice::MOUSE);

	////Keyboard Actions
	//InputManager::Instance()->AddAction("horn", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);
	//InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	//InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	//InputManager::Instance()->AddAction("up", SDL_SCANCODE_UP, InputManager::eDevice::KEYBOARD);
	//InputManager::Instance()->AddAction("down", SDL_SCANCODE_DOWN, InputManager::eDevice::KEYBOARD);

	////Text
	//text = TextManager::Instance()->CreateText("Hello!", "..\\content\\Inconsolata-Bold.ttf", 24, Color::red);

	////Entity Creation
	//Entity* entity = new Entity(ID("player"));
	//TransformComponent* transformComponent = new TransformComponent(entity);
	//transformComponent->Create(Vector2D(400.0f, 500.0f));
	//entity->AddComponent(transformComponent);

	//SpriteComponent* spriteComponent = new SpriteComponent(entity);
	//spriteComponent->Create("..\\content\\ship.bmp");
	//entity->AddComponent(spriteComponent);

	//ShipControllerComponent* shipControllerComponent = new ShipControllerComponent(entity);
	//shipControllerComponent->Create(200.0f);
	//entity->AddComponent(shipControllerComponent);

	//m_scene->AddEntity(entity);
	
	//
	m_running = success;

	return success;
}

void Game::Shutdown()
{
	m_engine->Shutdown();
}

void Game::Update()
{
	m_running = !m_engine->IsQuit();
	m_engine->Update();

	m_scene->Update();

	//int x, y;
	//SDL_GetMouseState(&x, &y);

	//const Uint8* keystate = SDL_GetKeyboardState(nullptr);

	////Pause
	//if (InputManager::Instance()->GetButtonState(SDL_SCANCODE_RETURN) == InputManager::eButtonState::PRESSED)
	//{
	//	(Timer::Instance()->IsPaused()) ? Timer::Instance()->Unpause() : Timer::Instance()->Pause();
	//}

	////Movement
	//if (InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED ||
	//	InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD)
	//{
	//	angle -= 180.0f * Timer::Instance()->DeltaTime();
	//}

	//if (InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED ||
	//	InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD)
	//{
	//	angle += 180.0f * Timer::Instance()->DeltaTime();
	//}

	////float steer = InputManager::Instance()->GetActionRelative("steer");
	////angle += (steer * 200.0f) * Timer::Instance()->DeltaTime();

	//Vector2D force = Vector2D::zero;
	//if (InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::PRESSED ||
	//	InputManager::Instance()->GetActionButton("up") == InputManager::eButtonState::HELD)
	//{
	//	force.y = -300.0f * Timer::Instance()->DeltaTime();
	//}

	//if (InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::PRESSED ||
	//	InputManager::Instance()->GetActionButton("down") == InputManager::eButtonState::HELD)
	//{
	//	force.y = 300.0f * Timer::Instance()->DeltaTime();
	//}

	////Sound
	//if (InputManager::Instance()->GetActionButton("horn") == InputManager::eButtonState::PRESSED)
	//{
	//	std::cout << "beep\n";
	//	AudioSystem::Instance()->PlaySound("horn", false);
	//}
	//if (InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED)
	//{
	//	std::cout << "pew\n";
	//	AudioSystem::Instance()->PlaySound("laser", false);
	//}

	//Matrix22 mx;
	//mx.Rotate(angle * Math::DegreesToRadians);
	//force = force * mx;
	//position += force;

	////DRAW
	//Renderer::Instance()->BeginFrome();
	//Renderer::Instance()->SetColor(Color::black);

	//float xy = InputManager::Instance()->GetActionRelative("steer");
	//std::string str = std::to_string(x);


	//std::vector<Color> colors = { Color::red, Color::green, Color::white };
	////text->SetText("Hello World", colors[rand() % colors.size()]);
	//text->SetText(str, colors[rand() % colors.size()]);
	//text->Draw(Vector2D(10.0f, 10.0f), 0.0f);

	//SDL_Texture* texture = TextureManager::Instance()->GetTexture("..\\content\\car.bmp");
	//Renderer::Instance()->DrawTexture(texture, position, angle);
	////Renderer::Instance()->DrawTexture(texture, position, scalar, 0.0f);

	//entity->Draw();

	//Renderer::Instance()->EndFrame();

	Renderer::Instance()->BeginFrome();
	Renderer::Instance()->SetColor(Color(0.0f, 0.8f, 1.0f));

	m_scene->Draw();

	Renderer::Instance()->EndFrame();
}