#include "CInputKeyboard.h"

//For debug purposes
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"

CInputKeyboard::CInputKeyboard()
{
}

CInputKeyboard::~CInputKeyboard()
{
}

void CInputKeyboard::StartUp(void)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"Starting Up CInputKeyboard!");
	AddEvent(EVENT_TYPE_SDL, SDL_KEYUP);
	AddEvent(EVENT_TYPE_SDL, SDL_KEYDOWN);

	RegisterEventManager();
}

void CInputKeyboard::ShutDown(void)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"Shutting Down CInputKeyboard!");
	UnRegisterEventManager();
}

void CInputKeyboard::Update(f64 dt)
{
}

void CInputKeyboard::HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event)
{
	if (a_Event == NULL)
		return;


	switch(a_Event->type)
	{
		case SDL_KEYDOWN:
			KeyScancodeDown(a_Event->key.keysym.scancode);
		break;
		case SDL_KEYUP:
			KeyScancodeUp(a_Event->key.keysym.scancode);
		break;

		default:
			// TODO
			break;
	}
}

void CInputKeyboard::KeyScancodeDown(SDL_Scancode a_Scancode)
{
	KeyScancodeUpdate(a_Scancode,true);
}

void CInputKeyboard::KeyScancodeUp(SDL_Scancode a_Scancode)
{
	KeyScancodeUpdate(a_Scancode,false);
}

void CInputKeyboard::KeyScancodeUpdate(SDL_Scancode a_Scancode, bool a_ScancodeState)
{
	auto l_SCode = m_RegisteredInputScancodes.find(a_Scancode);

	//Update the keyscancode state if exists
	if ( l_SCode != m_RegisteredInputScancodes.end())
		l_SCode->second = a_ScancodeState;

}

bool CInputKeyboard::InsertKeyAction(const std::string &a_ActionName, const std::string &a_RawKeyName )
{
	SDL_Scancode l_scancode = SDL_GetScancodeFromName(a_RawKeyName.c_str());
	//TODO check if this is a valid scancode


	//Check if that actionname exists if not exists add it to both maps
	if (m_RegisteredKeyActions.find(a_ActionName) == m_RegisteredKeyActions.end())
	{

		m_RegisteredKeyActions[a_ActionName] = l_scancode;

		//Init the scancode to false (Keyup) if not exists
		if (m_RegisteredInputScancodes.find(l_scancode) == m_RegisteredInputScancodes.end())
			m_RegisteredInputScancodes[l_scancode] = false;

		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"CInputKeyboard::InsertKeyAction ADDED -> Action: %s  SDL_ScanCode: %d",
				a_ActionName.c_str(),l_scancode);

		return true;
	}

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_WARNING, LOGSUB_INPUT,"CInputKeyboard::InsertKeyAction ACTION-> Action: %s Exists!!  SDL_ScanCode: %d",
			a_ActionName.c_str(),l_scancode);

	return false;
}

bool	CInputKeyboard::IsActionKeyPressed(const std::string &a_ActionName)
{
	auto l_Action = m_RegisteredKeyActions.find(a_ActionName);

	if ( l_Action != m_RegisteredKeyActions.end())
		return m_RegisteredInputScancodes[l_Action->second];

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"CInputKeyboard::IsActionKeyPressed -> Action: %s  Not exists!",
					a_ActionName.c_str());
	//If not exists return false;
	return false;

}
