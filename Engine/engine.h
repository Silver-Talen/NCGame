#pragma once

#include "sdl.h"

#ifdef ENGINE_EXPORTS  
#define ENGINE_API __declspec(dllexport)   
#else  
#define ENGINE_API __declspec(dllimport)   
#endif 

class ENGINE_API Engine
{
public:
	Engine() {}
	~Engine() {}
};