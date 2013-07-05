#include "CTimeManager.h"
#include "Core/CCoreEngine.h"
#include "Core/CLogManager.h"
#include "SDL2/SDL.h"

static const u32  INVALID_TIMERID = 0;

CTimeManager::CTimeManager():
m_CurrentTimerID(INVALID_TIMERID)
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_TIMER,"Object Created!");

	// Elapsed time (Delta)
	m_ElapsedTimeSeconds = 0.0F;
	m_LastTimeInMiliseconds = 0;


	m_LastFrameTimeArray.fill( 0.0F);
	m_itLastFrame = m_LastFrameTimeArray.begin();


	// FPS
	m_FramesPerSecond = 0.0F;

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

	UpdateTimers();

//CCoreEngine::Instance().GetLogManager().LogOutput(LOG_INFO, LOGSUB_TIMER,"dTime = %F  |  FPS = %F   %d", m_ElapsedTimeSeconds ,m_FramesPerSecond);
}


void	CTimeManager::CalculateElapsedTime()
{
	const u32 l_CurrentMiliseconds = SDL_GetTicks();

	if (!m_LastTimeInMiliseconds)
		m_LastTimeInMiliseconds = l_CurrentMiliseconds;

	// Add frame time to frame samples array (seconds)
	f64	l_DeltaInMiliseconds 	=	l_CurrentMiliseconds - m_LastTimeInMiliseconds;
	f64	l_lastframeSeconds 		=  	l_DeltaInMiliseconds * 0.001F; 	//convert to seconds

	*m_itLastFrame = l_lastframeSeconds;

	m_LastTimeInMiliseconds = l_CurrentMiliseconds;



	// Calculate Elapsed time based on frame samples array
	f64 l_deltasSum = 0;
	for (auto value : m_LastFrameTimeArray)
		l_deltasSum += value;


	m_ElapsedTimeSeconds = l_deltasSum / m_LastFrameTimeArray.size();

	if (++m_itLastFrame == m_LastFrameTimeArray.end())
		m_itLastFrame = m_LastFrameTimeArray.begin();


}

EV_TimerID CTimeManager::CreateTimer(const f64 a_DurationInSeconds,const bool a_looped, void (*a_func)(EV_TimerID ))
{
	++m_CurrentTimerID; // TODO POT DONAR LA VOLTA ARREGLAR! (OVERFLOW)
	EV_TimerInfo	l_NewTimer(m_CurrentTimerID, m_LastTimeInMiliseconds, a_DurationInSeconds,a_looped,a_func);
	// TODO use .emplace and check if the timer was inserted.
	m_TimersMap.insert(std::pair<u32,EV_TimerInfo>(m_CurrentTimerID,l_NewTimer));

	return m_CurrentTimerID;
}



void CTimeManager::UpdateTimers()
{
	// How many timers finished?
	std::vector<EV_TimerID >	l_TimersExpired;
	for (auto &l_Timer: m_TimersMap )
		if (l_Timer.second.IsEnd() && !l_Timer.second.IsLoop())
			l_TimersExpired.push_back(l_Timer.first);

	// Delete expired timers
	for (auto &l_IDToDelete: l_TimersExpired )
		m_TimersMap.erase(l_IDToDelete);

	// Update remaining timers
	for (auto &l_Timer: m_TimersMap )
		l_Timer.second.Update(m_LastTimeInMiliseconds);
}

bool CTimeManager::KillTimer(const EV_TimerID a_TimerID)
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

bool	CTimeManager::IsEndTimer(const EV_TimerID id) const
{
	auto l_itToErase =  m_TimersMap.find(id);
	if (l_itToErase	== m_TimersMap.end() )
	{
		CCoreEngine::Instance().GetLogManager().LogOutput(LOG_ERROR, LOGSUB_TIMER,"IsTimerIDEnd - Timer Not Found!");
		return false;
	}
	else
		return l_itToErase->second.IsEnd();

}

void	CTimeManager::CalculateFPS()
{
	static u32 	l_FPScount = 0;		// Frame counter
	static f64	l_ETAccumSeconds = 0; // Elapsed time seconds accumulation per frame


	++l_FPScount;
	l_ETAccumSeconds += m_ElapsedTimeSeconds;
	m_FramesPerSecond = l_FPScount/l_ETAccumSeconds;

	if(	l_ETAccumSeconds > 1.0 ) //Every second
	{
		l_ETAccumSeconds = l_ETAccumSeconds - 1.0;
		l_FPScount = 0;
	}
}

f64 CTimeManager::GetElapsedTimeSeconds() const
{
	return m_ElapsedTimeSeconds;
}

f64 CTimeManager::GetFPS() const
{
	return m_FramesPerSecond;
}

