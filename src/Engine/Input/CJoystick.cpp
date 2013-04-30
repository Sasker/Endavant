#include "CJoystick.h"

#define AXIS_MOVEMENT_THRESHOLD 3200

CJoystick::CJoystick(SDL_Joystick* a_Joystick) :
	m_Joystick(a_Joystick),
	m_X_Axis(X_AXIS_DIRECTION_NULL),
	m_Y_Axis(Y_AXIS_DIRECTION_NULL)
{
	for (Uint32 index = 0; index < (Uint32)SDL_JoystickNumButtons(m_Joystick); ++index)
	{
		m_PressedButtons.push_back(false);
	}
}

CJoystick::~CJoystick()
{

}

void CJoystick::Close()
{
	SDL_JoystickClose(m_Joystick);

	for (Uint32 index = 0; index < m_PressedButtons.size(); ++index)
	{
		m_PressedButtons[index] = false;
	}
}

void CJoystick::HandleAxisMotion(SDL_Event* a_Event)
{
	const SDL_JoyAxisEvent& Axis = a_Event->jaxis;

	// Izquierda - Derecha
	if (Axis.axis == 0 && Axis.value < -AXIS_MOVEMENT_THRESHOLD)
	{
		m_X_Axis = X_AXIS_DIRECTION_LEFT;
	}
	else if (Axis.axis == 0 && Axis.value > AXIS_MOVEMENT_THRESHOLD)
	{
		m_X_Axis = X_AXIS_DIRECTION_RIGHT;
	}
	else
	{
		m_X_Axis = X_AXIS_DIRECTION_NULL;
	}

	// Arriba - Abajo
	if (Axis.axis == 1 && Axis.value < -AXIS_MOVEMENT_THRESHOLD)
	{
		m_Y_Axis = Y_AXIS_DIRECTION_UP;
	}
	else if (Axis.axis == 1 && Axis.value > AXIS_MOVEMENT_THRESHOLD)
	{
		m_Y_Axis = Y_AXIS_DIRECTION_DOWN;
	}
	else
	{
		m_Y_Axis = Y_AXIS_DIRECTION_NULL;
	}
}

void CJoystick::HandleBallMotion(SDL_Event* a_Event)
{

}

void CJoystick::HandleHatMotion(SDL_Event* a_Event)
{

}

void CJoystick::HandleButtonDown(SDL_Event* a_Event)
{
	if (a_Event->jaxis.which < m_PressedButtons.size())
	{
		m_PressedButtons[a_Event->jaxis.which] = true;
	}
}

void CJoystick::HandleButtonUp(SDL_Event* a_Event)
{
	if (a_Event->jaxis.which < m_PressedButtons.size())
	{
		m_PressedButtons[a_Event->jaxis.which] = false;
	}
}
