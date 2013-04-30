#include "CInputManager.h"
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"
using namespace std;

CInputManager::CInputManager()
{

}

CInputManager::~CInputManager()
{

}

void CInputManager::StartUp()
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"Starting Up!");

	m_MouseInput.StartUp();
	m_KeyboardInput.StartUp();
	m_JoystickInput.StartUp();
}

void CInputManager::ShutDown()
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_INPUT,"Shutting Down!");

	m_MouseInput.ShutDown();
	m_KeyboardInput.ShutDown();
	m_JoystickInput.ShutDown();
}

void CInputManager::Update(float dt)
{
	m_MouseInput.Update(dt);
	m_KeyboardInput.Update(dt);
	m_JoystickInput.Update(dt);
}
