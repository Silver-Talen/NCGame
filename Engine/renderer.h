#pragma once
#include "singleton.h"
#include "engine.h"

class Renderer : public Singleton<Renderer>
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();

protected:
	Renderer() {}
	~Renderer() {}

private:
	Engine * m_engine;
};