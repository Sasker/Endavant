#include "CTimeManager.h"
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"
#include "SDL2/SDL.h"

//
//static float		m_pLastFramesTime[FRAME_SAMPLES_COUNT];

static const u32  INVALID_TIMERID = 0;

CTimeManager::CTimeManager():
m_CurrentTimerID(INVALID_TIMERID)

{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_TIMER,"Object Created!");

	// Elapsed time (Delta)
	m_currentElapsedTime = 0.0F;
	m_LastTicks = 0;
	m_TotalTimeInSeconds = 0.0F;
	m_LastFrameTimeArray.fill( 0.0F);
	m_itLastFrame = m_LastFrameTimeArray.begin();


	// FPS
	m_FPScount = 0;
	m_FPStime = 0.0F;
	m_FPS = 0.0F;

}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::StartUp(void)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_TIMER,"StartUp");
}

void CTimeManager::ShutDown(void)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_TIMER,"ShutDown");
}

void CTimeManager::Update(f64 dt)
{
	CalculateElapsedTime();
	CalculateFPS();
	//UpdateTimers();

	//CCoreEngine::Instance().GetLogManager().LogOutput(LOG_INFO, LOGSUB_TIMER,"dTime = %F  |  FPS = %F | FPStime = %f", m_currentElapsedTime ,m_FPS, m_FPStime );
}


void	CTimeManager::CalculateElapsedTime()
{
	u32 l_currentticks = SDL_GetTicks();

	if (!m_LastTicks)
		m_LastTicks = l_currentticks;

	// Add frame time to frame samples array (seconds)
	f64	l_ticksdiff = l_currentticks - m_LastTicks;
	f64	l_lastframeSeconds =  l_ticksdiff * 0.001F; 	//convert to seconds
	*m_itLastFrame = l_lastframeSeconds;

	// Update the total seconds
	m_TotalTimeInSeconds += l_lastframeSeconds;

	m_LastTicks = l_currentticks;

	// Calculate Elapsed time based on frame samples array
	f64 l_deltasSum = 0;
	for (auto value : m_LastFrameTimeArray)
		l_deltasSum += value;


	m_currentElapsedTime = l_deltasSum / m_LastFrameTimeArray.size();

	if (++m_itLastFrame == m_LastFrameTimeArray.end())
		m_itLastFrame = m_LastFrameTimeArray.begin();


}

bool CTimeManager::RegisterListener(ITimerListener* a_listener)
{
	if(a_listener == nullptr)
		return false;

	auto l_result = m_Listeners.insert(a_listener);
	if(!l_result.second)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_TIMER,"Could not Register TimerListener, pointer duplicated");

		return false;
	}
	else
		return true;



}

bool CTimeManager::UnregisterListener(ITimerListener* a_listener)
{
	auto l_result = m_Listeners.erase(a_listener);

	if (!l_result)
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_TIMER,"Could not UnRegister TimerListener, pointer not found");
		return false;
	}
	else
		return true;

}



TimerID CTimeManager::CreateTimer(ITimerListener const*  a_pListener,const f64 a_duration,
		const bool a_looped, void (*a_func)(TimerID id))
{

	TimerInfo	l_Timer;

	++m_CurrentTimerID;
	l_Timer.m_duration		= a_duration;
	l_Timer.m_func	  		= a_func;
	l_Timer.m_id	  		= m_CurrentTimerID;
	l_Timer.m_startTicks 	= SDL_GetTicks();
	l_Timer.m_looped	  	= a_looped;
	l_Timer.m_listener  	= a_pListener;

	// TODO use .emplace and check if the timer was inserted.
	m_TimersMap.insert(std::pair<u32,TimerInfo>(m_CurrentTimerID,l_Timer));

	return m_CurrentTimerID;

}

TimerID CTimeManager::CreateDelayedTimer(ITimerListener const*  a_pListener,const f64 a_duration,
		const bool a_looped = false, float delay = 0.0f, void (*a_func)(TimerID id) = nullptr)
{
	TimerInfo	l_Timer;

		++m_CurrentTimerID;
		l_Timer.m_duration		= a_duration;
		l_Timer.m_func	  		= a_func;
		l_Timer.m_id	  		= m_CurrentTimerID;
		l_Timer.m_startTicks 	= SDL_GetTicks();
		l_Timer.m_looped	  	= a_looped;
		l_Timer.m_listener  	= a_pListener;

		// TODO use .emplace and check if the timer was inserted.
		m_TimersMap.insert(std::pair<u32,TimerInfo>(m_CurrentTimerID,l_Timer));

		return m_CurrentTimerID;

}

bool CTimeManager::StartDelayedTimer(TimerID a_TimerID)
{
	return false;
}

bool CTimeManager::KillTimer(TimerID a_TimerID)
{

	auto l_itToErase =  m_TimersMap.find(a_TimerID);
	if (l_itToErase	== m_TimersMap.end() )
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_TIMER,"KillTimer - Timer Not Found!");
		return false;
	}
	else
	{
		m_TimersMap.erase(l_itToErase);
		return true;
	}
}

void	CTimeManager::CalculateFPS()
{
	++m_FPScount;
	m_FPStime += m_currentElapsedTime;

	m_FPS = m_FPScount/m_FPStime;

	if(	m_FPStime > 1.0 ) //Every second
	{
		m_FPStime = m_FPStime - 1.0;
		m_FPScount = 0;
	}

}

f64 CTimeManager::GetElapsedTime() const
{
	return m_currentElapsedTime;
}

f64 CTimeManager::GetFPS() const
{
	return m_FPS;
}

