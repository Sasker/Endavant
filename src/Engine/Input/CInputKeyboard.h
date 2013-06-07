#ifndef CINPUT_KEYBOARD_H_
#define CINPUT_KEYBOARD_H_

#include "SDL2/SDL.h"
#include "Core/CBasicTypes.h"

#include <string>
#include <unordered_map>
#include <map>

#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"

class CKeyStatus
{
	public:

		CKeyStatus():CKeyStatus(""){};
		CKeyStatus(const std::string &a_RawKey):
			m_RawKey(a_RawKey), m_Pressed(false), m_Pressing(false),m_SDLScancode(SDL_GetScancodeFromName(a_RawKey.c_str())){}


		std::string  m_RawKey;	// Key raw string read
		bool		 m_Pressed;
		bool		 m_Pressing;
		SDL_Scancode m_SDLScancode;	// SDLScancode used to compare with the keyboard input
		//SDL_Keycode  m_SDLKeyCode;	// Keycode used to compare with the keyboard input

};


class CInputKeyboard
{
public:
	CInputKeyboard();
	~CInputKeyboard();
	void 	Update();

	// Insert an action to the associated RawKeyName. RawKeyName will use the SDL convention found here: wiki.libsdl.org/moin.fcg/SDL_Keycode
	bool	InsertKeyAction(const std::string &a_ActionName, const std::string &a_RawKeyName );
	//bool	InsertKeyAction(const std::string a_ActionName, const SDL_Keycode a_SDLKeyCode );

private:
	u8 		*m_KeyBoardState;


	//Contains all the registered input key actions with their current State/Info
	typedef std::map<std::string, CKeyStatus>	t_KeyActionsMap;
	t_KeyActionsMap	m_RegisteredKeyActions;

};

#endif
