#ifndef CINPUT_KEYBOARD_H_
#define CINPUT_KEYBOARD_H_

#include <string>
#include "Core/ISubSystem.h"
#include "SDL2/SDL.h"

class CInputKeyboard : public ISubSystem
{
public:
	CInputKeyboard();
	~CInputKeyboard();

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);

	bool IsKeyPressed(const std::string& key) const;

private:
	Uint8 		*m_KeyBoardState;

};

#endif
