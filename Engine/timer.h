#pragma once
#include "singleton.h"
#include "engine.h"

class ENGINE_API Timer : public Singleton<Timer>
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	float DeltaTime() const { return m_dt * m_timeScale; }
	float UnscaledDeltaTime() const { return m_dt; }

	void SetTimeScale(float timeScale) { m_timeScale = timeScale; }
	float GetTimeScacle() const { return m_timeScale; }

	void Pause() { m_paused = true; }
	void Unpause() { m_paused = false; }
	bool IsPaused() const { return m_paused; }

	friend Singleton<Timer>;

protected:
	Timer() {}
	~Timer() {}

private:
	Engine * m_engine;
	float m_dt;
	Uint32 m_prevTicks;
	bool m_paused;
	float m_timeScale;
};