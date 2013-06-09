#include "SDL2/SDL.h"
#include "CInputMouse.h"
#include "Events/CEventCodes.h"



CInputMouse::CInputMouse():
m_MousePosition(0,0),
m_MouseRelativePosition(0,0),
m_left_mouse_pressed(false),
m_right_mouse_pressed(false),
m_middle_mouse_pressed(false)
{
}

CInputMouse::~CInputMouse()
{

}

void CInputMouse::StartUp(void)
{
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEMOTION);
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEBUTTONDOWN);
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEBUTTONUP);
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEWHEEL);

	RegisterEventManager();

	// Create Translation table
	m_translateStrToMouseType["MOUSE_X"]	= MOUSE_X;
	m_translateStrToMouseType["MOUSE_Y"]	= MOUSE_Y;
	m_translateStrToMouseType["MOUSE_Z"]	= MOUSE_Z;
	m_translateStrToMouseType["MOUSE_LB"]	= MOUSE_LB;
	m_translateStrToMouseType["MOUSE_MB"]	= MOUSE_MB;
	m_translateStrToMouseType["MOUSE_RB"]	= MOUSE_RB;

	//Estat inicial del mouse
	m_left_mouse_pressed = false;
	m_right_mouse_pressed = false;
	m_middle_mouse_pressed = false;

}

void CInputMouse::ShutDown(void)
{
	UnRegisterEventManager();
}

void CInputMouse::Update(f64 dt)
{

}

void CInputMouse::HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event)
{

	if (a_Event != NULL)
	{
		switch(a_Event->type)
		{
			case SDL_MOUSEBUTTONDOWN:
			{
				switch(a_Event->button.button)
				{
					case SDL_BUTTON_LEFT:
						m_left_mouse_pressed = true;
						MouseActionUpdate(MOUSE_LB, true);
						break;
					case SDL_BUTTON_RIGHT:
						m_right_mouse_pressed = true;
						MouseActionUpdate(MOUSE_RB, true);
						break;
					case SDL_BUTTON_MIDDLE:
						MouseActionUpdate(MOUSE_MB, true);
						m_middle_mouse_pressed = true;
						break;
				}
				break;
			}
			break;

			case SDL_MOUSEBUTTONUP:
			{
				switch(a_Event->button.button)
				{
					case SDL_BUTTON_LEFT:
						m_left_mouse_pressed = false;
						MouseActionUpdate(MOUSE_LB, false);
						break;
					case SDL_BUTTON_RIGHT:
						m_right_mouse_pressed = false;
						MouseActionUpdate(MOUSE_RB, false);
						break;
					case SDL_BUTTON_MIDDLE:
						m_middle_mouse_pressed = false;
						MouseActionUpdate(MOUSE_MB, false);
						break;
				}
				break;
			}
			break;

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


bool CInputMouse::IsButtonPressed(E_MOUSE mouse_button)
{

	switch(mouse_button)
	{
		case MOUSE_LB:
			return m_left_mouse_pressed;
			break;

		case MOUSE_RB:
			return m_right_mouse_pressed;
			break;

		case MOUSE_MB:
			return m_middle_mouse_pressed;
			break;
		default:
			return false;
			break;

	}
	return false;
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

			// Init the enum to false if not exists.
			if (m_RegisteredInputMouse.find(l_mouseinputenum->second) == m_RegisteredInputMouse.end())
				m_RegisteredInputMouse[l_mouseinputenum->second] = false;


			return true;
		}
		else
		{
			CCoreEngine::Instance().GetLogManager().LogOutput( LOG_WARNING, LOGSUB_INPUT ,"InsertButtonAction: Action Exists" );
			return false; // TODO inform that this action exists.
		}


	}
	else
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_INPUT ,"InsertButtonAction: Action Exists" );
		return false; // TODO inform that a bad a_RawMouseButtonName was given.
	}


}

bool	CInputMouse::IsActionActive(const std::string &a_ActionName)
{
	auto l_Action = m_RegisteredMouseActions.find(a_ActionName);

	if ( l_Action != m_RegisteredMouseActions.end())
		return m_RegisteredInputMouse[l_Action->second];

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_WARNING, LOGSUB_INPUT ,"IsActionActive: Action NOT Exists" );
	return false;

}

void CInputMouse::MouseActionUpdate(E_MOUSE a_MouseButton, bool a_ValueToUpdate)
{
	auto l_ButtonStatus = m_RegisteredInputMouse.find(a_MouseButton);
	if (l_ButtonStatus != m_RegisteredInputMouse.end() )
		l_ButtonStatus->second = a_ValueToUpdate;
}
