#include "CEventHandler.h"
#include "Core/CCoreEngine.h"
#include "CEventManager.h"

CEventHandler::CEventHandler() :
	m_Registered(false)
{

}

CEventHandler::~CEventHandler()
{

}

void CEventHandler::AddEvent(Uint32 a_Type, Uint32 a_Code)
{
	if (!m_Registered)
	{
		m_TypeList[a_Type].insert(a_Code);
	}
}

void CEventHandler::RegisterEventManager()
{
	CCoreEngine::Instance().GetEventManager().Register(m_TypeList, this);

	m_Registered = true;
}

void CEventHandler::UnRegisterEventManager()
{
	CCoreEngine::Instance().GetEventManager().UnRegister(m_TypeList, this);

	m_Registered = false;
	m_TypeList.clear();
}
