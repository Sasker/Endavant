#include "CInputJoystick.h"
#include "Input/CJoystick.h"
#include "Events/CEventCodes.h"

CInputJoystick::CInputJoystick()
{

}

CInputJoystick::~CInputJoystick()
{

}

void CInputJoystick::StartUp(void)
{
	AddEvent(EVENT_TYPE_SDL, SDL_JOYAXISMOTION);
	AddEvent(EVENT_TYPE_SDL, SDL_JOYBALLMOTION);
	AddEvent(EVENT_TYPE_SDL, SDL_JOYHATMOTION);
	AddEvent(EVENT_TYPE_SDL, SDL_JOYBUTTONDOWN);
	AddEvent(EVENT_TYPE_SDL, SDL_JOYBUTTONUP);
	RegisterEventManager();

	LoadJoysticks();
}

void CInputJoystick::ShutDown(void)
{
	UnRegisterEventManager();
	CloseAllJoysticks();
}

void CInputJoystick::Update(f64 dt)
{
	if (SDL_NumJoysticks() != (int)m_Joysticks.size())
	{
		CloseAllJoysticks();
		LoadJoysticks();
	}
}

void CInputJoystick::HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event)
{
	if (a_Event == NULL)
		return;
/* TODO
	switch(a_Event->type)
	{
	case SDL_JOYAXISMOTION:
		if (a_Event->jaxis.which < m_Joysticks.size())
			m_Joysticks[a_Event->jaxis.which].HandleAxisMotion(a_Event);
		break;
	case SDL_JOYBALLMOTION:
		if (a_Event->jaxis.which < m_Joysticks.size())
			m_Joysticks[a_Event->jaxis.which].HandleBallMotion(a_Event);
		break;
	case SDL_JOYHATMOTION:
		if (a_Event->jaxis.which < m_Joysticks.size())
			m_Joysticks[a_Event->jaxis.which].HandleHatMotion(a_Event);
		break;
	case SDL_JOYBUTTONDOWN:
		if (a_Event->jaxis.which < m_Joysticks.size())
			m_Joysticks[a_Event->jaxis.which].HandleButtonDown(a_Event);
		break;
	case SDL_JOYBUTTONUP:
		if (a_Event->jaxis.which < m_Joysticks.size())
			m_Joysticks[a_Event->jaxis.which].HandleButtonUp(a_Event);
		break;
	}
	*/
}

std::string CInputJoystick::GetJoystickName(Uint32 a_Index)
{
	if (a_Index < m_Joysticks.size())
	{
		return m_Joysticks[a_Index].GetName();
	}

	return "";
}

Uint32 CInputJoystick::GetJoystickNumButtons(Uint32 a_Index)
{
	if (a_Index < m_Joysticks.size())
	{
		return m_Joysticks[a_Index].GetNumButtons();
	}

	return 0;
}

Uint32 CInputJoystick::GetJoystickNumAxes(Uint32 a_Index)
{
	if (a_Index < m_Joysticks.size())
	{
		return m_Joysticks[a_Index].GetNumAxes();
	}

	return 0;
}

void CInputJoystick::CloseAllJoysticks()
{
	for (Uint32 index = 0; index < m_Joysticks.size(); ++index)
	{
		m_Joysticks[index].Close();
	}

	m_Joysticks.clear();
}

void CInputJoystick::LoadJoysticks()
{
	SDL_JoystickEventState(SDL_ENABLE);

	for (Uint32 index = 0; index < (Uint32)SDL_NumJoysticks(); ++index)
	{
		m_Joysticks.push_back(CJoystick(SDL_JoystickOpen(index)));
	}
}
