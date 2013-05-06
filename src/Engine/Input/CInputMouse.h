#ifndef CINPUT_MOUSE_H_
#define CINPUT_MOUSE_H_

#include "Events/CEventHandler.h"
#include "Core/ISubSystem.h"

enum MOUSE_BUTTONS
{
	MOUSE_LEFT_BUTTON = 0,
	MOUSE_MIDDLE_BUTTON,
	MOUSE_RIGHT_BUTTON
};

class CInputMouse : public ISubSystem, public CEventHandler
{
public:
	CInputMouse();
	~CInputMouse();

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);

	// CEventHandler
	void HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event = NULL);

	inline int	GetMousePosX() {return m_mouse_pos_X;};
	inline int	GetMousePosY() {return m_mouse_pos_Y;};
	SDL_Rect 	GetMousePosRect();
	bool 		IsMouseButtonPressed(MOUSE_BUTTONS mouse_button);

private:
	int 	m_mouse_pos_X, m_mouse_pos_Y;
	bool	m_left_mouse_pressed;
	bool	m_right_mouse_pressed;
	bool	m_middle_mouse_pressed;
};

#endif
