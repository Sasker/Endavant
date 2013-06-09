#ifndef CINPUT_KEYBOARD_H_
#define CINPUT_KEYBOARD_H_

#include "SDL2/SDL.h"
#include "Core/CBasicTypes.h"
#include "Events/CEventHandler.h"
#include "Events/CEventCodes.h"
#include "Core/ISubSystem.h"

#include <string>
//TODO the maps in this class should be unordered_maps
//#include <unordered_map>
#include <map>

class CInputKeyboard: public ISubSystem , public CEventHandler
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	// Insert an action to the associated RawKeyName. RawKeyName will use the SDL convention found here: wiki.libsdl.org/moin.fcg/SDL_Keycode
	bool	InsertKeyAction(const std::string &a_ActionName, const std::string &a_RawKeyName );

	//Returns true if the key for the given action is down / false if the key is up
	bool	IsActionKeyPressed(const std::string &a_ActionName);

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);

	// CEventHandler
	void 	HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event = nullptr);

private:

	void KeyScancodeDown(SDL_Scancode a_Scancode);
	void KeyScancodeUp(SDL_Scancode a_Scancode);
	void KeyScancodeUpdate(SDL_Scancode a_Scancode, bool a_ScancodeState);

	//Contains all the registered input key actions with their current State/Info
	typedef std::map< std::string, SDL_Scancode >	t_KeyActionsMap;
	t_KeyActionsMap		m_RegisteredKeyActions;

	//Contains all the registered input Scancodes and their status (true = keydown, false = keyup)
	typedef std::map< SDL_Scancode, bool >			t_KeyScanStatusMap;
	t_KeyScanStatusMap	m_RegisteredInputScancodes;


};

#endif
