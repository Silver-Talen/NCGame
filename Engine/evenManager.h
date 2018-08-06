#pragma once

#include "engine.h"
#include "event.h"
#include "singleton.h"

	class ENGINE_API EvenManager : public Singleton<EvenManager>
	{
	public:
		bool Initialize(Engine* engine);
		void Shutdown();
		void Update();

		void SendMessage(const Event& event);

	protected:
		friend Singleton<EvenManager>;

	protected:
		Engine * m_engine;
	};