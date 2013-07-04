#include "CInputKeyboard.h"

//For debug purposes
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"

CInputKeyboard::CInputKeyboard():
m_KeyBoardState(nullptr)
{
}

CInputKeyboard::~CInputKeyboard()
{
}

void CInputKeyboard::StartUp(void)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"Starting Up CInputKeyboard!");
}

void CInputKeyboard::ShutDown(void)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"Shutting Down CInputKeyboard!");
}

void CInputKeyboard::Update(f64 dt)
{
	//Get the current keyboardstate
	m_KeyBoardState = SDL_GetKeyboardState(NULL);

	UpdateKeyActions();
}

void CInputKeyboard::UpdateKeyActions()
{
	for (auto &l_action: m_RegisteredInputScancodes)
	{
		if ( m_KeyBoardState[l_action.first] )
		{
			if (l_action.second == EV_KEY_UP)
				l_action.second = EV_KEY_DOWN;
			else
				l_action.second = EV_KEY_PUSHREPEAT;
		}
		else
			l_action.second = EV_KEY_UP;

	}
}

bool CInputKeyboard::InsertKeyAction(const std::string &a_ActionName, const std::string &a_RawKeyName )
{
	SDL_Scancode l_scancode = SDL_GetScancodeFromName(a_RawKeyName.c_str());

	// Check if the scancode is valid
	if ( l_scancode == SDL_SCANCODE_UNKNOWN)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_INPUT,"CInputKeyboard::InsertKeyAction The Scancode is UNKNOWN -> Action: %s  SDL_ScanCode: %d",
						a_ActionName.c_str(),l_scancode);

		return false;
	}


	//Check if that actionname exists if not exists add it to both maps
	if (m_RegisteredKeyActions.find(a_ActionName) == m_RegisteredKeyActions.end())
	{

		m_RegisteredKeyActions[a_ActionName] = l_scancode;

		//Init the scancode to false (Keyup) if not exists
		if (m_RegisteredInputScancodes.find(l_scancode) == m_RegisteredInputScancodes.end())
			m_RegisteredInputScancodes[l_scancode] = EV_KEY_UP;

		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"CInputKeyboard::InsertKeyAction ADDED -> Action: %s  SDL_ScanCode: %d",
				a_ActionName.c_str(),l_scancode);

		return true;
	}

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_WARNING, LOGSUB_INPUT,"CInputKeyboard::InsertKeyAction ACTION-> Action: %s Exists!!  SDL_ScanCode: %d",
			a_ActionName.c_str(),l_scancode);

	return false;
}

bool	CInputKeyboard::IsActionKeyPushed(const std::string &a_ActionName)
{
	// tambe comprovem el KEY_DOWN, sino saltem 1 frame (i la tecla si k esta apretada)
	return IsActionKeyStatus(a_ActionName, EV_KEY_PUSHREPEAT) || IsActionKeyStatus(a_ActionName, EV_KEY_DOWN);
}

bool CInputKeyboard::IsActionKeyUp(const std::string& a_ActionName)
{
	return IsActionKeyStatus(a_ActionName, EV_KEY_UP);
}

bool CInputKeyboard::IsActionKeyDown(const std::string& a_ActionName)
{
	return IsActionKeyStatus(a_ActionName, EV_KEY_DOWN);
}

bool CInputKeyboard::IsActionKeyStatus(const std::string& a_ActionName, EV_KeyStatus a_KeyStatus)
{
	auto l_Action = m_RegisteredKeyActions.find(a_ActionName);

	if ( l_Action != m_RegisteredKeyActions.end())
	{
		if (m_RegisteredInputScancodes[l_Action->second] == a_KeyStatus)
			return true;
		else
			return false;
	}

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"CInputKeyboard::IsActionKeyStatus -> Action: %s  Not exists!",
			a_ActionName.c_str());
	//If not exists return false;
	return false;
}
