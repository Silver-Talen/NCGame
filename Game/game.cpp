#include "game.h"
#include "engine.h"
#include "scene.h"
#include "textManager.h"
#include "textureManager.h"
#include "renderer.h"
#include "entity.h"
#include "spriteComponent.h"
#include "textComponent.h"
#include "ship.h"
#include "enemy.h"
#include "fileSystem.h"

//Vector2D position(400.0f, 300.0f);
//Vector2D scalar(5.0f, 5.0f);
//float angle = 0.0f;
//Text* text;
bool Game::Initialize()
{
	bool success = m_engine->Initialize();
	FileSystem::Instance()->SetPathname("..\\galaga\\");
	m_scene = new Scene();

	Entity* entity = new Entity(m_scene);
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	TextComponent* textComponent = entity->AddComponent<TextComponent>();
	textComponent->Create("hello", "emulogic.ttf", 12, Color::blue);
	textComponent->SetDepth(100);
	m_scene->AddEntity(entity);
	
	/*Entity* entity = new Entity(m_scene);
	entity->GetTransform().position = Vector2D(400.0f, 300.0f);
	SpriteComponent* spriteComponent = entity->AddComponent<SpriteComponent>();
	spriteComponent->Create("galaga.png", Vector2D(0.5f, 0.5f));
	spriteComponent->SetDepth(100);
	m_scene->AddEntity(entity);*/

	Ship* ship = new Ship(m_scene, "player");
	ship->Create(Vector2D(400.0f, 550.0f));
	m_scene->AddEntity(ship);
		
	for (size_t i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy(m_scene);
		float x = Math::GetRandomRange(25.0f, Renderer::Instance()->GetSize().x - 25.0f);
		float y = Math::GetRandomRange(-225.0f, -Renderer::Instance()->GetSize().y);
		enemy->Create(Vector2D(x, y), 3.0f);
		m_scene->AddEntity(enemy);
	}

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

	Renderer::Instance()->BeginFrame();

	m_scene->Update();
	Renderer::Instance()->SetColor(Color::black);
	m_scene->Draw();

	Renderer::Instance()->EndFrame();

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
}