#include "CInputKeyboard.h"
#include <utility>

CInputKeyboard::CInputKeyboard():
m_KeyBoardState(nullptr)
{


}

CInputKeyboard::~CInputKeyboard()
{

}

void CInputKeyboard::Update()
{

	m_KeyBoardState = SDL_GetKeyboardState(0);

	//Update all registered actions state.
	for (auto& l_action : m_RegisteredKeyActions )
	{

		if ( m_KeyBoardState[l_action.second.m_SDLScancode] )
		{
			CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_EVENTS, "ACTION: %s Active | Key: %s", l_action.first.c_str(), l_action.second.m_RawKey.c_str());
		}
	}
}


bool CInputKeyboard::InsertKeyAction(const std::string &a_ActionName, const std::string &a_RawKeyName )
{
	auto l_itAction = m_RegisteredKeyActions.find(a_ActionName);

	if (l_itAction == m_RegisteredKeyActions.end())
	{
		m_RegisteredKeyActions[a_ActionName] = CKeyStatus(a_RawKeyName);
		return true;
	}

	//TODO log warning keyaction exists
	return false;
}

