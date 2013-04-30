#ifndef CINPUT_JOYSTICK_H_
#define CINPUT_JOYSTICK_H_

#include <vector>
#include <string>
#include "SDL2/SDL.h"
#include "Events/CEventHandler.h"
#include "ISubSystem.h"

class CJoystick;

class CInputJoystick : public ISubSystem, public CEventHandler
{
public:
	typedef std::vector< CJoystick > t_JoystickList;

	CInputJoystick();
	~CInputJoystick();

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(float dt);

	// CEventHandler
	void HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event = NULL);

	std::string GetJoystickName(Uint32 a_Index);
	Uint32 		GetJoystickNumButtons(Uint32 a_Index);
	Uint32 		GetJoystickNumAxes(Uint32 a_Index);

private:
	void CloseAllJoysticks();
	void LoadJoysticks();

	t_JoystickList m_Joysticks;

};

#endif
