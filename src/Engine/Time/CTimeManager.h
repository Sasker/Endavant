/*
 * CTimeManager.h
 *
 *  Created on: 25/01/2013
 *      Author: dani
 */

#ifndef CTIMEMANAGER_H_
#define CTIMEMANAGER_H_

#include "Core/ISubSystem.h"
#include "Core/CBasicTypes.h"
#include <set>
#include <list>
#include <map>
#include <memory>
#include <array>

typedef u32 TimerID;


class ITimerListener
{
public:
	virtual void OnTimer(TimerID id) = 0;
	virtual ~ITimerListener();
};


struct TimerInfo
{
	TimerID m_id;				// unsigned integer timer identifier, set by CTimeManager
	bool 	m_delayed;				// indicates if a timer is a delayed timer, set by CTimeManager
	bool 	m_started;				// indicates if a delayed timer is already started, set by CTimeManager
	f64 	m_startTime;			// actual start time of the timer in seconds, set by CTimeManager
	f64 	m_delay;				// time (in seconds) after which a delayed timer starts automatically
	f64 	m_duration;				// duration of the timer in seconds

	void (*m_func) (TimerID id);// optional pointer to a function which should be called after the timer is expired
	bool m_looped;				// indicates if it is a looped timer
	ITimerListener const* m_listener;	// the listener this timer belongs to

	TimerInfo(const TimerID a_ID, const f64 a_duration, const f64 a_delay,  )
	{
		m_id			= 0;
		m_delayed		= false;
		m_started		= false;
		m_startTicks	= 0;
		m_duration		= 0.0f;
		m_func			= nullptr;
		m_delay			= 0.0f;
		m_looped        = false;
		m_listener		= nullptr;
	}
};

class CTimeManager: public ISubSystem
{
public:

	CTimeManager();
	virtual ~CTimeManager();

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);


	f64 GetElapsedTime() const;		//!< Get Delta time in seconds
	f64 GetFPS() const;				//!< Get Frames per second

	bool RegisterListener(ITimerListener* listener);		// Registers a timer listener, which gets informed after a timer is expired.
	bool UnregisterListener(ITimerListener* listener);		// Unregisters / Deletes a timer listener

	bool StartDelayedTimer(TimerID id);						// Starts a delayed timer, even if it has a specified delay time.
	bool KillTimer(TimerID id);								// Kills / Deletes a timer with the given timer identifier.

	// Creates a timer with a given duration time. The function pointer is optional and the function
	// it points to will be called after the timer is expired. If the optional parameter looped is set to true, the timer will
	// be restarted after expiration (until the timer will be deleted with a KillTimer call).
	// Returns the timer identifier, which should be stored, so it is possible to kill/delete the timer with a KillTimer call.
	TimerID CreateTimer(ITimerListener const*  a_pListener,const f64 a_duration,const bool a_looped = false, void (*a_func)(TimerID id) = nullptr);
    TimerID CreateTimer(float duration, bool looped = false, void (*func) (TimerID id) = NULL)
	{
		return CreateTimer(NULL, duration, looped, func);
	};

	// Creates a delayed timer, which is either started automatically after the optional delay time is expired or
	// (if the delay time is set to 0.0f) will be started after a StartDelayedTimer call.
    TimerID CreateDelayedTimer(ITimerListener const*  a_pListener,const f64 a_duration,const bool a_looped = false, float delay = 0.0f, void (*a_func)(TimerID id) = nullptr);
	TimerID CreateDelayedTimer(float duration, bool looped = false, float delay = 0.0f, void (*func) (TimerID id) = NULL)
	{
		return CreateDelayedTimer(NULL, duration, looped, delay, func);
	};

private:

    // TIME
	void	CalculateElapsedTime();
	void	CalculateFPS();
	static const u32 FRAME_SAMPLES_COUNT = 1;
	typedef std::array<f64,FRAME_SAMPLES_COUNT> t_LastFramesArray;

    f64 m_currentElapsedTime;
    f64 m_TotalTimeInSeconds;
	u32 m_LastTicks;
	t_LastFramesArray					m_LastFrameTimeArray;
	t_LastFramesArray::iterator			m_itLastFrame;

	// FPS
	u32 m_FPScount;
	f64 m_FPStime;
	f64 m_FPS;

    // TIMERS
    typedef std::set<ITimerListener*>			ITimerListener_ptr;
    ITimerListener_ptr							m_Listeners;


    typedef std::map<TimerID, TimerInfo>		t_TimersInfoMap;
	t_TimersInfoMap								m_TimersMap;

	TimerID										m_CurrentTimerID;
};



#endif /* CTIMEMANAGER_H_ */
