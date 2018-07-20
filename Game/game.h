#pragma once

class Engine;

class Game
{
public:
	Game(Engine* engine) : m_engine(engine) {}
	~Game() {}

	bool Initialize();
	void Update();
	void Shutdown();

	bool Run() { return m_running; }

protected:
	bool m_running = false;
	Engine* m_engine = nullptr;
};