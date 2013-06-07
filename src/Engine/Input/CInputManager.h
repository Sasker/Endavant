#ifndef CINPUTMANAGER_H_
#define CINPUTMANAGER_H_
#include <SDL2/SDL.h>
#include <unordered_map>
#include <string>
#include <vector>
#include "Core/ISubSystem.h"
#include "CInputMouse.h"
#include "CInputKeyboard.h"
#include "CInputJoystick.h"




class CInputManager : public ISubSystem//,  public CEventHandler
{
public:
	~CInputManager();

	// ISubSystem
	void	StartUp(void);
	void	ShutDown(void);
	void 	Update(f64 dt);

	bool	RegisterAction(std::string a_ActionID);
	//inline const CInputMouse& 	GetMouse() { return m_MouseInput; }
	inline const CInputKeyboard& 	GetKeyboard() { return m_KeyboardInput; }
	//inline const CInputJoystick& 	GetJoysticks() { return m_JoystickInput; }

	// CEventHandler
//	void HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event = NULL);

private:

	CInputManager(); friend class CCoreEngine;




	//CInputMouse 	m_MouseInput;
	CInputKeyboard 	m_KeyboardInput;
	//CInputJoystick	m_JoystickInput;



};

#endif /* CINPUTMANAGER_H_ */
