#ifndef CTIMER_H_
#define CTIMER_H_

#include "CBasicTypes.h"

class CTimer
{
public:
	CTimer(uint a_Duration, uint a_Start);
	~CTimer();

	bool 		Finished();
	void 		Update(uint a_LastTick);
	uint		GetID();

private:
	static uint	m_NextID;

	uint		m_ID;
	uint 		m_Duration;
	uint 		m_Start;
	bool 		m_Finished;
};

#endif
