#include <iostream>
#include "CEventManager.h"
#include "Core/CCoreEngine.h"
#include "CEventCodes.h"
#include "Core/CLogManager.h"

CEventManager::CEventManager()
{

}

CEventManager::~CEventManager()
{

}

void CEventManager::StartUp(void)
{

}

void CEventManager::ShutDown(void)
{

}

void CEventManager::Update(f64 dt)
{
	SDL_Event l_Event;

	while (SDL_PollEvent(&l_Event))
	{
		Uint32 l_Type = EVENT_TYPE_SDL;
		Uint32 l_Code = l_Event.type;


		//CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_EVENTS, "EVENT!");
		switch(l_Event.type)
		{
			case SDL_QUIT:
				CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_EVENTS, "EVENT SDL_QUIT");
				CCoreEngine::Instance().StopCore();
				return;

			case SDL_USEREVENT:
				l_Type = *(Uint32*)l_Event.user.data1;
				l_Code = l_Event.user.code;
				delete (Uint32*)l_Event.user.data1;
				break;
			default:
				break;
		}

		t_ListenersGroup& l_Group = m_Listeners[l_Type][l_Code];
		for (t_ListenersGroup::iterator itGrp = l_Group.begin(); itGrp != l_Group.end(); ++itGrp)
		{
			(*itGrp)->HandleEvent(l_Type, l_Code, &l_Event);
		}
	}
}

void CEventManager::Register(const CEventHandler::t_TypeList& a_TypeList, CEventHandler* a_Listener)
{
	for (CEventHandler::t_TypeList::const_iterator itType = a_TypeList.begin(); itType != a_TypeList.end(); ++itType)
	{
		const CEventHandler::t_CodeList& CodeList = itType->second;
		for (CEventHandler::t_CodeList::const_iterator itCode = CodeList.begin(); itCode != CodeList.end(); ++itCode)
		{
			m_Listeners[itType->first][(*itCode)].insert(a_Listener);
		}
	}
}

void CEventManager::UnRegister(const CEventHandler::t_TypeList& a_TypeList, CEventHandler* a_Listener)
{
	for (CEventHandler::t_TypeList::const_iterator itType = a_TypeList.begin(); itType != a_TypeList.end(); ++itType)
	{
		const CEventHandler::t_CodeList& CodeList = itType->second;
		for (CEventHandler::t_CodeList::const_iterator itCode = CodeList.begin(); itCode != CodeList.end(); ++itCode)
		{
			m_Listeners[itType->first][(*itCode)].erase(a_Listener);
		}
	}
}

void CEventManager::PushEvent(Uint32 a_Type, Uint32 a_Code)
{
	//@TODO anyadir "userdata" en data2
	SDL_Event l_Event;
	l_Event.type = SDL_USEREVENT;
	l_Event.user.type = SDL_USEREVENT;
	l_Event.user.code = a_Code;
	l_Event.user.data1 = (void*)new Uint32;
	*(Uint32*)l_Event.user.data1 = a_Type;

	SDL_PushEvent(&l_Event);
}
