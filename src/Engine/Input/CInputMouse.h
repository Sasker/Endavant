#ifndef CINPUT_MOUSE_H_
#define CINPUT_MOUSE_H_

#include "Events/CEventHandler.h"
#include "Core/ISubSystem.h"
#include "glm/glm.hpp"


#include <string>
#include <map>
#include <array>

enum EV_MOUSE_BUTTON
{
	EV_MOUSE_LB = SDL_BUTTON_LEFT,
	EV_MOUSE_MB = SDL_BUTTON_MIDDLE,
	EV_MOUSE_RB = SDL_BUTTON_RIGHT,
	EV_MOUSE_X1 = SDL_BUTTON_X1,
	EV_MOUSE_X2 = SDL_BUTTON_X2,

	EV_MOUSE_MAXBUTTONS = 5
};




class CInputMouse : public CEventHandler, public ISubSystem
{
public:
	CInputMouse();
	~CInputMouse();

	// Insert an action to the associated E_MOUSE
	bool	InsertButtonAction(const std::string &a_ActionName, const std::string &a_RawKeyName );

	//Returns true if the key for the given action is pressed down / false if the key isn't
	bool	IsActionButtonPushed(const std::string &a_ActionName);

	//Returns true if the key for the given action is Key Up
	bool	IsActionButtonUp(const std::string &a_ActionName);

	//Returns true if the key for the given is first keydown
	bool	IsActionButtonDown(const std::string &a_ActionName);



	//Getters
	inline s32			GetPosX() 		{return m_MousePosition.x;};
	inline s32			GetPosY() 		{return m_MousePosition.y;};
	inline glm::ivec2 	GetPos()		{return m_MousePosition;};
	inline s32			GetPosRelX() 	{return m_MouseRelativePosition.x;};
	inline s32			GetPosRelY() 	{return m_MouseRelativePosition.y;};
	inline glm::ivec2 	GetPosRel()		{return m_MouseRelativePosition;};




	//CEventHandler
	void HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event=NULL);

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);

private:

	typedef enum
	{
		EV_MOUSEBUTTON_UP = 0,
		EV_MOUSEBUTTON_DOWN,
		EV_MOUSEBUTTON_PUSHREPEAT

	}EV_MOUSE_BUTTON_STATUS;

	bool IsActionButtonStatus(const std::string &a_ActionName, const EV_MOUSE_BUTTON_STATUS a_ButtonStatus);
	void MouseActionUpdate(EV_MOUSE_BUTTON a_MouseButton, bool a_ValueToUpdate);

	// Current button state
	std::array<EV_MOUSE_BUTTON_STATUS,EV_MOUSE_MAXBUTTONS> 	m_MouseButtonsState;

	// Current mouse position
	glm::ivec2		m_MousePosition;
	glm::ivec2		m_MouseRelativePosition;

	// Translation table
	typedef	std::map<std::string, EV_MOUSE_BUTTON>	t_MapStringToMouseType;
	t_MapStringToMouseType					m_translateStrToMouseType;

	//Contains all the registered input mouse actions with their current State/Info
	typedef std::map< std::string, EV_MOUSE_BUTTON >	t_MouseActionsMap;
	t_MouseActionsMap		m_RegisteredMouseActions;


};

#endif
