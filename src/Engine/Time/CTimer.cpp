#include "CTimer.h"

uint CTimer::m_NextID = 0;

CTimer::CTimer(uint a_Duration, uint a_Start) :
	m_ID(m_NextID++),
	m_Duration(a_Duration),
	m_Start(a_Start),
	m_Finished(false)
{

}

CTimer::~CTimer()
{

}

bool CTimer::Finished()
{
	return m_Finished;
}

void CTimer::Update(uint a_LastTick)
{
	if (a_LastTick - m_Start >= m_Duration)
	{
		m_Finished = true;
	}
}

uint CTimer::GetID()
{
	return m_ID;
}
