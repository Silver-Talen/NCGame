#pragma once
#include "singleton.h"
#include "engine.h"

class InputManager
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();

protected:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
};