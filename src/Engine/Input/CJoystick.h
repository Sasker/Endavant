#ifndef CJOYSTICK_H_
#define CJOYSTICK_H_

#include <vector>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_joystick.h"

enum E_X_AXIS_DIRECTIONS
{
	X_AXIS_DIRECTION_NULL = 0,
	X_AXIS_DIRECTION_LEFT,
	X_AXIS_DIRECTION_RIGHT,
};

enum E_Y_AXIS_DIRECTIONS
{
	Y_AXIS_DIRECTION_NULL = 0,
	Y_AXIS_DIRECTION_UP,
	Y_AXIS_DIRECTION_DOWN,
};

class CJoystick
{
public:
	CJoystick(SDL_Joystick* a_Joystick);
	~CJoystick();

	inline std::string	GetName() 		{ return m_Joystick? SDL_JoystickName(m_Joystick) : ""; }
	inline Uint32		GetNumButtons() { return m_Joystick? SDL_JoystickNumButtons(m_Joystick) : 0; }
	inline Uint32 		GetNumAxes() 	{ return m_Joystick? SDL_JoystickNumAxes(m_Joystick) : 0; }

	inline const E_X_AXIS_DIRECTIONS& 	GetXAxisDirection() { return m_X_Axis; }
	inline const E_Y_AXIS_DIRECTIONS& 	GetYAxisDirection() { return m_Y_Axis; }
	inline bool IsButtonPressed(Uint32 a_Index) { return a_Index < m_PressedButtons.size()? m_PressedButtons[a_Index] : false; }

	void Close();

	void HandleAxisMotion(SDL_Event* a_Event);
	void HandleBallMotion(SDL_Event* a_Event);
	void HandleHatMotion(SDL_Event* a_Event);
	void HandleButtonDown(SDL_Event* a_Event);
	void HandleButtonUp(SDL_Event* a_Event);

private:
	SDL_Joystick* 		m_Joystick;
	E_X_AXIS_DIRECTIONS m_X_Axis;
	E_Y_AXIS_DIRECTIONS m_Y_Axis;
	std::vector<bool>	m_PressedButtons;
};

#endif
