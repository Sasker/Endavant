#ifndef CINPUTMANAGER_H_
#define CINPUTMANAGER_H_
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>
#include "Core/ISubSystem.h"
#include "CInputMouse.h"
#include "CInputKeyboard.h"
#include "CInputJoystick.h"

class CInputManager : public ISubSystem
{
public:
	~CInputManager();

	// ISubSystem
	void	StartUp(void);
	void	ShutDown(void);
	void 	Update(float dt);

	inline const CInputMouse& 		GetMouse() { return m_MouseInput; }
	inline const CInputKeyboard& 	GetKeyboard() { return m_KeyboardInput; }
	inline const CInputJoystick& 	GetJoysticks() { return m_JoystickInput; }

private:
	friend class CCoreEngine;
	CInputManager();

	CInputMouse 	m_MouseInput;
	CInputKeyboard 	m_KeyboardInput;
	CInputJoystick	m_JoystickInput;

};

#endif /* CINPUTMANAGER_H_ */
