#ifndef CINPUT_KEYBOARD_H_
#define CINPUT_KEYBOARD_H_

#include "SDL2/SDL.h"
#include "Core/CBasicTypes.h"
#include "Core/ISubSystem.h"

#include <string>
//TODO the maps in this class should be unordered_maps
//#include <unordered_map>
#include <map>

class CInputKeyboard: public ISubSystem
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	// Insert an action to the associated RawKeyName. RawKeyName will use the SDL convention found here: wiki.libsdl.org/moin.fcg/SDL_Keycode
	bool	InsertKeyAction(const std::string &a_ActionName, const std::string &a_RawKeyName );

	//Returns true if the key for the given action is pressed down / false if the key isn't
	bool	IsActionKeyPushed(const std::string &a_ActionName);

	//Returns true if the key for the given action is Key Up
	bool	IsActionKeyUp(const std::string &a_ActionName);

	//Returns true if the key for the given is first keydown
	bool	IsActionKeyDown(const std::string &a_ActionName);




	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);


private:

	typedef enum
	{
		EV_KEY_UP = 0,
		EV_KEY_DOWN,
		EV_KEY_PUSHREPEAT

	}EV_KeyStatus;


	bool IsActionKeyStatus(const std::string& a_ActionName, EV_KeyStatus a_KeyStatus);
	void UpdateKeyActions();

	//Mantains the state of the keyboard updated every frame
	const Uint8 *	m_KeyBoardState;

	//Contains all the registered input key actions with their current State/Info
	typedef std::map< std::string, SDL_Scancode >	t_KeyActionsMap;
	t_KeyActionsMap		m_RegisteredKeyActions;

	//Contains all the registered input Scancodes and their status EV_KeyStatus
	typedef std::map< SDL_Scancode, EV_KeyStatus >			t_KeyScanStatusMap;
	t_KeyScanStatusMap	m_RegisteredInputScancodes;


};

#endif
