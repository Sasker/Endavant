#ifndef CINPUTMANAGER_H_
#define CINPUTMANAGER_H_
#include "Core/ISubSystem.h"
#include "CInputMouse.h"
#include "CInputKeyboard.h"
#include "CInputJoystick.h"

#include <string>

class CInputManager : public ISubSystem
{
public:
	~CInputManager();

	void LoadActionsXML(const std::string &a_FileName){};//TODO IMPLEMENT

	inline CInputMouse& 	GetMouse() { return m_MouseInput; }
	inline CInputKeyboard& 	GetKeyboard() { return m_KeyboardInput; }
	inline CInputJoystick& 	GetJoysticks() { return m_JoystickInput; }

	// ISubSystem
	void	StartUp(void);
	void	ShutDown(void);
	void 	Update(f64 dt);

private:

	CInputManager(); friend class CCoreEngine;

	CInputMouse 	m_MouseInput;
	CInputKeyboard 	m_KeyboardInput;
	CInputJoystick	m_JoystickInput;



};

#endif /* CINPUTMANAGER_H_ */
