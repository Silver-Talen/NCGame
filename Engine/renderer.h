#pragma once
#include "singleton.h"
#include "engine.h"
#include "color.h"
#include "vector2D.h"

class Renderer : public Singleton<Renderer>
{
public:

	bool Initialize(Engine* engine);
	void Shutdown();

	SDL_Renderer* GetRenderer() { return m_renderer; }

	void BeginFrome();
	void EndFrame();

	void SetColor(const Color& color);
	void DrawTexture(SDL_Texture* texture, const Vector2D& position, float angle);
	void DrawTexture(SDL_Texture* texture, const Vector2D& position, const Vector2D& scale, float angle);

	friend Singleton<Renderer>;

protected:
	Renderer() {}
	~Renderer() {}

private:
	Engine * m_engine;
	SDL_Renderer* m_renderer = nullptr;
};