/*
 * CTimeManager.h
 *
 *  Created on: 25/01/2013
 *      Author: dani
 */

#ifndef CTIMEMANAGER_H_
#define CTIMEMANAGER_H_

#include "ISubSystem.h"
#include "CBasicTypes.h"
#include <vector>
#include "CTimer.h"

class CTimeManager: public ISubSystem
{
public:
	CTimeManager();

	void StartUp(void);
	void ShutDown(void);

	void Update(float dt);


	float 	GetElapsedTime() const;		//!< Get Delta time in seconds
	float	GetFPS() const;				//!< Get Frames per second


	uint 		CreateTimer(uint a_Duration);
	bool		TimerFinished(uint a_ID);

	virtual ~CTimeManager();

private:
	typedef std::vector< CTimer > t_Timers;

	void		CalculateElapsedTime();
	uint		m_LastTicks;
	float		m_currentElapsedTime;
	uint		m_LastFrameIndex;


	void		CalculateFPS();
	uint		m_FPScount;
	float		m_FPStime;
	float		m_FPS;

	void		UpdateTimers();
	t_Timers	m_Timers;
};

#endif /* CTIMEMANAGER_H_ */
