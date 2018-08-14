#pragma once

#include "eventReceiver.h"

class Engine;
class Scene;
class StateMachine;

class Game : public EventReceiver
{
public:
	Game(Engine* engine) : m_engine(engine) {}
	~Game() {}

	bool Initialize();
	void Update();
	void Shutdown();

	void OnEvent(const Event& event);

	bool Run() { return m_running; }

protected:
	size_t m_score = 0;

	bool m_running = false;
	Engine* m_engine = nullptr;
	Scene* m_scene = nullptr;
	StateMachine* m_stateMachine = nullptr;
};