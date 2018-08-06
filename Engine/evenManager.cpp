#include "evenManager.h"
#include "entity.h"

bool EvenManager::Initialize(Engine * engine)
{
	m_engine = engine;

	return false;
}

void EvenManager::Shutdown()
{

}

void EvenManager::Update()
{

}

void EvenManager::SendMessage(const Event & event)
{
	event.reciever->OnEvent(event);
}