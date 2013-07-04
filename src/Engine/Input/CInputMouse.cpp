#include "SDL2/SDL.h"
#include "CInputMouse.h"
#include "Events/CEventCodes.h"

//For debug purposes
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"


CInputMouse::CInputMouse():
m_MousePosition(0,0),
m_MouseRelativePosition(0,0)
{
}

CInputMouse::~CInputMouse()
{

}

void CInputMouse::StartUp(void)
{
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEMOTION);
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEWHEEL);

	RegisterEventManager();

	// Create Translation table
	m_translateStrToMouseType["MOUSE_LB"]	= EV_MOUSE_LB;
	m_translateStrToMouseType["MOUSE_MB"]	= EV_MOUSE_MB;
	m_translateStrToMouseType["MOUSE_RB"]	= EV_MOUSE_RB;
	m_translateStrToMouseType["MOUSE_X1"]	= EV_MOUSE_X1;
	m_translateStrToMouseType["MOUSE_X2"]	= EV_MOUSE_X2;


}

void CInputMouse::ShutDown(void)
{
	UnRegisterEventManager();
}

void CInputMouse::Update(f64 dt)
{
	//Get current mouse state
	auto l_CurrMouseState = SDL_GetMouseState(NULL, NULL);

	// Update all Mouse states
	for (auto &l_MouseButton: m_MouseButtonsState)
	{
		if ( l_CurrMouseState & SDL_BUTTON(l_MouseButton))
		{
			if (l_MouseButton == EV_MOUSEBUTTON_UP)
				l_MouseButton = EV_MOUSEBUTTON_DOWN;
			else
				l_MouseButton = EV_MOUSEBUTTON_PUSHREPEAT;
		}
		else
			l_MouseButton = EV_MOUSEBUTTON_UP;
	}

}


bool CInputMouse::IsActionButtonPushed(const std::string& a_ActionName)
{
	return IsActionButtonStatus(a_ActionName,EV_MOUSEBUTTON_PUSHREPEAT) || IsActionButtonStatus(a_ActionName,EV_MOUSEBUTTON_DOWN);
}

bool CInputMouse::IsActionButtonUp(const std::string& a_ActionName)
{
	return IsActionButtonStatus(a_ActionName,EV_MOUSEBUTTON_UP);
}

bool CInputMouse::IsActionButtonDown(const std::string& a_ActionName)
{
	return IsActionButtonStatus(a_ActionName,EV_MOUSEBUTTON_DOWN);
}

bool	CInputMouse::IsActionButtonStatus(const std::string &a_ActionName, const EV_MOUSE_BUTTON_STATUS a_ButtonStatus)
{
	auto l_Action = m_RegisteredMouseActions.find(a_ActionName);

	if ( l_Action != m_RegisteredMouseActions.end())
	{
		if (m_MouseButtonsState[l_Action->second] == a_ButtonStatus)
			return true;
		else
			return false;
	}

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_WARNING, LOGSUB_INPUT ,"IsActionActive: Action NOT Exists" );
	return false;
}



void CInputMouse::HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event)
{
	if (a_Event != NULL)
	{
		switch(a_Event->type)
		{
			case SDL_MOUSEMOTION:
			{
				m_MousePosition.x = a_Event->motion.x;
				m_MousePosition.y = a_Event->motion.y;
				m_MouseRelativePosition.x = a_Event->motion.xrel;
				m_MouseRelativePosition.y = a_Event->motion.yrel;
			}
			break;

		}

	}
}


bool CInputMouse::InsertButtonAction(const std::string &a_ActionName, const std::string &a_RawMouseButtonName )
{
	auto l_mouseinputenum = m_translateStrToMouseType.find(a_RawMouseButtonName);

	if ( l_mouseinputenum != m_translateStrToMouseType.end() )
	{
		//Check if that actionname exists if not exists add it to both maps
		if (m_RegisteredMouseActions.find(a_ActionName) == m_RegisteredMouseActions.end())
		{
			m_RegisteredMouseActions[a_ActionName] = l_mouseinputenum->second;
			return true;
		}
		else
		{
			CCoreEngine::Instance().GetLogManager().LogOutput( LOG_WARNING, LOGSUB_INPUT ,"InsertButtonAction: Action Exists" );
			return false;
		}

	}
	else
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_INPUT ,"InsertButtonAction: Action Exists" );
		return false;
	}


}



