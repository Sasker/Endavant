#include "SDL2/SDL.h"
#include "CInputMouse.h"
#include "Events/CEventCodes.h"

CInputMouse::CInputMouse()
{

}

CInputMouse::~CInputMouse()
{

}

void CInputMouse::StartUp(void)
{
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEMOTION);
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEBUTTONDOWN);
	AddEvent(EVENT_TYPE_SDL, SDL_MOUSEBUTTONUP);
	RegisterEventManager();

	//Estat inicial del mouse
	m_left_mouse_pressed = false;
	m_right_mouse_pressed = false;
	m_middle_mouse_pressed = false;
	SDL_GetMouseState(&m_mouse_pos_X,&m_mouse_pos_Y);
}

void CInputMouse::ShutDown(void)
{
	UnRegisterEventManager();
}

void CInputMouse::Update(f64 dt)
{
	SDL_GetMouseState(&m_mouse_pos_X,&m_mouse_pos_Y); //Actualitzem les coordenades del ratoli
}

void CInputMouse::HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event)
{
	if (a_Event != NULL)
	{
		switch(a_Event->type)
		{
		case SDL_MOUSEBUTTONDOWN:
			switch(a_Event->button.button)
			{
				case SDL_BUTTON_LEFT:
					m_left_mouse_pressed = true;
				//	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOG_INPUT,"SDL_MOUSEBUTTONDOWN - LEFT");
					break;
				case SDL_BUTTON_RIGHT:
					m_right_mouse_pressed = true;
				//	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOG_INPUT,"SDL_MOUSEBUTTONDOWN - RIGHT");
					break;
				case SDL_BUTTON_MIDDLE:
					m_middle_mouse_pressed = true;
				//	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOG_INPUT,"SDL_MOUSEBUTTONDOWN - MIDDLE");
					break;
			}
			break;

		case SDL_MOUSEBUTTONUP:
			switch(a_Event->button.button)
			{
				case SDL_BUTTON_LEFT:
					m_left_mouse_pressed = false;
					//CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOG_INPUT,"SDL_MOUSEBUTTONUP - LEFT");
					break;
				case SDL_BUTTON_RIGHT:
					m_right_mouse_pressed = false;
				//	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOG_INPUT,"SDL_MOUSEBUTTONUP - RIGHT");
					break;
				case SDL_BUTTON_MIDDLE:
					m_middle_mouse_pressed = false;
				//	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOG_INPUT,"SDL_MOUSEBUTTONUP - MIDDLE");
					break;
			}
			break;
		}
	}
}

SDL_Rect CInputMouse::GetMousePosRect()
{
	SDL_Rect pos;
	pos.x = m_mouse_pos_X;
	pos.y = m_mouse_pos_Y;
	pos.w = 1;
	pos.h = 1;

	return pos;
}

bool CInputMouse::IsMouseButtonPressed(MOUSE_BUTTONS mouse_button)
{
	switch(mouse_button)
	{
		case MOUSE_LEFT_BUTTON:
			return m_left_mouse_pressed;

			break;
		case MOUSE_RIGHT_BUTTON:
			return m_right_mouse_pressed;

			break;

		case MOUSE_MIDDLE_BUTTON:
			return m_right_mouse_pressed;

			break;

	}
	return false;
}
