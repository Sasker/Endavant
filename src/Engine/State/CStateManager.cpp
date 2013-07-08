#include "CStateManager.h"
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"

CStateManager::CStateManager()
{

}

CStateManager::~CStateManager()
{

}

void CStateManager::StartUp()
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_STATE ,"StartUp");
}

void CStateManager::ShutDown()
{
	while (!m_StateStack.empty())
	{
		m_StateStack.top()->Cleanup();
		m_StateStack.pop();
	}

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_STATE ,"ShutDown");
}

void CStateManager::Update(f64 dt)
{
	if (!m_StateStack.empty())
		m_StateStack.top()->Update(dt);

}

void CStateManager::ChangeState(CState* state)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_STATE ,"ChangeState");
	// Pause current state and pop it from stack
	if (!m_StateStack.empty())
	{
		m_StateStack.top()->Pause();
		m_StateStack.pop();

	}

	// Store and init the new state.
	m_StateStack.push(state);
	m_StateStack.top()->Init();

}

void CStateManager::PushState(CState* state)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_STATE ,"PushState");
	// Pause current state
	if (!m_StateStack.empty())
		m_StateStack.top()->Pause();


	// Store and init the new state.
	m_StateStack.push(state);
	m_StateStack.top()->Init();

}



void CStateManager::PopState()
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_STATE ,"PopState");

	// Cleanup current state and pop it
	if (!m_StateStack.empty())
	{
		m_StateStack.top()->Cleanup();
		m_StateStack.pop();
	}

	// Resume the last state
	if (!m_StateStack.empty())
		m_StateStack.top()->Resume();

}
