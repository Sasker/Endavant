#ifndef CINPUT_MOUSE_H_
#define CINPUT_MOUSE_H_

#include "Events/CEventHandler.h"
#include "Core/ISubSystem.h"
#include "glm/glm.hpp"

//For debug purposes
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"

#include <string>
#include <map>

enum E_MOUSE_BUTTONS
{
	MOUSE_LB,
	MOUSE_MB,
	MOUSE_RB
};



class __declspec(dllexport) CInputMouse : public CEventHandler, public ISubSystem
{
public:
	CInputMouse();
	~CInputMouse();

	// Insert an action to the associated E_MOUSE
	bool	InsertButtonAction(const std::string &a_ActionName, const std::string &a_RawKeyName );

	//Returns true if the key for the given action is down / false if the key is up
	bool	IsActionActive(const std::string &a_ActionName);



	//Getters
	inline s32			GetPosX() 		{return m_MousePosition.x;};
	inline s32			GetPosY() 		{return m_MousePosition.y;};
	inline glm::ivec2 	GetPos()		{return m_MousePosition;};
	inline s32			GetPosRelX() 	{return m_MouseRelativePosition.x;};
	inline s32			GetPosRelY() 	{return m_MouseRelativePosition.y;};
	inline glm::ivec2 	GetPosRel()	{return m_MouseRelativePosition;};
	bool 				IsButtonPressed(E_MOUSE_BUTTONS mouse_button);



	//CEventHandler
	void HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event=NULL);

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);

private:



	void MouseActionUpdate(E_MOUSE_BUTTONS a_MouseButton, bool a_ValueToUpdate);

	glm::ivec2		m_MousePosition;
	glm::ivec2		m_MouseRelativePosition;

	bool			m_left_mouse_pressed;
	bool			m_right_mouse_pressed;
	bool			m_middle_mouse_pressed;

	// Translation table
	typedef	std::map<std::string, E_MOUSE_BUTTONS>	t_MapStringToMouseType;
	t_MapStringToMouseType					m_translateStrToMouseType;

	//Contains all the registered input mouse actions with their current State/Info
	typedef std::map< std::string, E_MOUSE_BUTTONS >	t_MouseActionsMap;
	t_MouseActionsMap		m_RegisteredMouseActions;

	//Contains all the registered input Scancodes and their status (true = keydown, false = keyup)
	typedef std::map< E_MOUSE_BUTTONS, bool >			t_MouseStatusMap;
	t_MouseStatusMap	m_RegisteredInputMouse;

};

#endif
