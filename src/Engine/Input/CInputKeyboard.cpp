#include "CInputKeyboard.h"
#include "Core/CCoreEngine.h"
#include "Time/CTimeManager.h"


CInputKeyboard::CInputKeyboard() :
	m_KeyBoardState(NULL)
{

}

CInputKeyboard::~CInputKeyboard()
{

}

void CInputKeyboard::StartUp(void)
{
	m_KeyBoardState = SDL_GetKeyboardState(0);
}

void CInputKeyboard::ShutDown(void)
{

}

void CInputKeyboard::Update(float dt)
{
	m_KeyBoardState = SDL_GetKeyboardState(0);
}

bool CInputKeyboard::IsKeyPressed(const std::string& key) const
{
	if (m_KeyBoardState == NULL)
		return false;

	if (m_KeyBoardState[SDL_GetScancodeFromName(key.c_str())])
	{
		return true;
	}

	return false;
}
