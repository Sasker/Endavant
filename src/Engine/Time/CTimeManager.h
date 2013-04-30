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
#include <vector>
#include <list>


typedef uint TimerID;

class ITimerListener
{
public:
	virtual void OnTimer(TimerID id) = 0;
	virtual ~ITimerListener();
};


struct TimerEx
{
	TimerID id;				// unsigned integer timer identifier, set by CTimerManager
	bool delayed;				// indicates if a timer is a delayed timer, set by CTimerManager
	bool started;				// indicates if a delayed timer is already started, set by CTimerManager
	float startTime;			// actual start time of the timer (in seconds since game start), set by CTimerManager

	float duration;				// duration of the timer in seconds
	void (*func) (TimerID id);	        // optional pointer to a function which should be called after the timer is expired
	float delay;				// time (in seconds) after which a delayed timer starts automatically
	bool looped;				// indicates if it is a looped timer
        ITimerListener* listener;               // the listener this timer belongs to

	TimerEx()
	{
		id		= 0;
		delayed		= false;
		started		= false;
		startTime	= 0.0f;

		duration	= 0.0f;
		func		= NULL;
		delay		= 0.0f;
                looped          = false;
                listener	= NULL;
	}
};

class CTimeManager: public ISubSystem
{
public:

	CTimeManager(){};

	void StartUp(void){};
	void ShutDown(void){};
	void Update(float dt){};

	float GetElapsedTime() const{return 0;};		//!< Get Delta time in seconds
	float GetFPS() const{return 0;};				//!< Get Frames per second


	// Creates a timer with a given duration time. The function pointer is optional and the function
	// it points to will be called after the timer is expired. If the optional parameter looped is set to true, the timer will
	// be restarted after expiration (until the timer will be deleted with a KillTimer call).
	// Returns the timer identifier, which should be stored, so it is possible to kill/delete the timer with a KillTimer call.
	TimerID CreateTimer(ITimerListener* pListener, float duration, bool looped = false, void (*func) (TimerID id) = NULL);
        TimerID CreateTimer(float duration, bool looped = false, void (*func) (TimerID id) = NULL)
	{
		return CreateTimer(NULL, duration, looped, func);
	};

	// Creates a delayed timer, which is either started automatically after the optional delay time is expired or
	// (if the delay time is set to 0.0f) will be started after a StartDelayedTimer call.
	TimerID CreateDelayedTimer(ITimerListener* pListener, float duration, bool looped = false, float delay = 0.0f, void (*func) (TimerID id) = NULL);
        TimerID CreateDelayedTimer(float duration, bool looped = false, float delay = 0.0f, void (*func) (TimerID id) = NULL)
	{
		return CreateDelayedTimer(NULL, duration, looped, delay, func);
	};

	// Starts a delayed timer, even if it has a specified delay time.
	bool StartDelayedTimer(TimerID id);

	// Kills / Deletes a timer with the given timer identifier.
	bool KillTimer(TimerID id);

	// Returns a timer pointer by a given timer identifier or NULL
	TimerEx* GetTimer(TimerID id);

	// Registers a timer listener, which gets informed after a timer is expired.
	bool RegisterListener(ITimerListener* listener);

	// Unregisters / Deletes a timer listener
	bool UnregisterListener(ITimerListener* listener);

	// Should be called on every frame update e.g here: CGame::Update(bool haveFocus, unsigned int updateFlags)
	void Update();

        void ResetTimerID();

private:
        void ClearTimerList();

	std::vector <ITimerListener*>	m_ListenerVec;
	std::list <TimerEx*>		m_TimerList;
	TimerID				m_CurrentTimerID;
};



#endif /* CTIMEMANAGER_H_ */
