#include "CTimeManager.h"
#include "CCoreEngine.h"
#include "CLogManager.h"
#include "SDL2/SDL.h"

static const uint 	FRAME_SAMPLES_COUNT = 1;
static float		m_pLastFramesTime[FRAME_SAMPLES_COUNT];

CTimeManager::CTimeManager()
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_TIMER,"Object Created!");

	// Elapsed time (Delta)
	m_currentElapsedTime = 0.0F;
	for (uint i = 0; i < FRAME_SAMPLES_COUNT; ++i)
		m_pLastFramesTime[i] = 0.0F;
	m_LastFrameIndex = 0;
	m_LastTicks = 0;


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

void CTimeManager::Update(float dt)
{
	CalculateElapsedTime();
	CalculateFPS();
	UpdateTimers();

	//CCoreEngine::Instance().GetLogManager().LogOutput(LOG_INFO, LOGSUB_TIMER,"dTime = %F  |  FPS = %F | FPStime = %f", m_currentElapsedTime ,m_FPS, m_FPStime );
}


void	CTimeManager::CalculateElapsedTime()
{
	uint	l_currentticks     = SDL_GetTicks();

	if (!m_LastTicks)
		m_LastTicks = l_currentticks;

	// Add frame time to frame samples array (seconds)
	uint	l_ticksdiff = l_currentticks - m_LastTicks;
	float	l_lastframetime =  ((float) l_ticksdiff) * 0.001F;
	m_pLastFramesTime[m_LastFrameIndex] = l_lastframetime;
	m_LastTicks = l_currentticks;

	// Calculate Elapsed time based on frame samples array
	float l_deltas = 0;
	for (uint i = 0; i < FRAME_SAMPLES_COUNT; ++i)
	{
		l_deltas += m_pLastFramesTime[i];
	}

	m_currentElapsedTime = l_deltas / (float) FRAME_SAMPLES_COUNT;
	++m_LastFrameIndex;
	m_LastFrameIndex %= FRAME_SAMPLES_COUNT;

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

float CTimeManager::GetElapsedTime() const
{
	return m_currentElapsedTime;
}

float CTimeManager::GetFPS() const
{
	return m_FPS;
}

uint CTimeManager::CreateTimer(uint a_Duration)
{
	m_Timers.push_back(CTimer(a_Duration, m_LastTicks));
	return m_Timers.back().GetID();
}

bool CTimeManager::TimerFinished(uint a_ID)
{
	t_Timers::iterator itTimers = m_Timers.begin();
	while(itTimers != m_Timers.end())
	{
		if (itTimers->GetID() == a_ID)
		{
			return false;
		}

		itTimers++;
	}

	return true;
}

void CTimeManager::UpdateTimers()
{
	t_Timers::iterator itTimers = m_Timers.begin();
	while(itTimers != m_Timers.end())
	{
		itTimers->Update(m_LastTicks);

		if (itTimers->Finished())
		{
			itTimers = m_Timers.erase(itTimers);
			continue;
		}

		itTimers++;
	}
}
