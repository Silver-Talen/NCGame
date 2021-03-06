#pragma once
#include "engine.h"
#include "singleton.h"
#include <string>

class ENGINE_API FileSystem : public Singleton<FileSystem>
{
public:
	bool Initialize(Engine* engine);
	void Shutdown();
	void Update();

	void SetPathname(const std::string& pathName) { m_pathName = pathName; }
	const std::string GetPathName() { return m_pathName; }

protected:
	Engine * m_engine;
	std::string m_pathName;
};