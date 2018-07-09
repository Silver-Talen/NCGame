#pragma once
#include "singleton.h"
#include "engine.h"

class InputManager : public Singleton<InputManager>
{
public:
	enum eAction
	{
		IDLE,
		PRESSED,
		HELD,
		RELEASED
	};

public:

	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	eAction GetButtonAction(SDL_Scancode scancode);

	friend Singleton<InputManager>;

protected:
	InputManager() {}
	~InputManager() {}

private:
	Engine * m_engine;
	Uint8* m_prevKeystate;
	Uint8* m_keystate;
	Uint8* m_prevMousestate;
	Uint8* m_mousestate;
	int m_numKeys;
};