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

typedef u32 EV_TimerID;

class CTimeManager: public ISubSystem
{
public:

	CTimeManager();
	virtual ~CTimeManager();

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);


	f64 GetElapsedTimeSeconds() const;		//!< Get Delta time in seconds
	f64 GetFPS() const;						//!< Get Frames per second


	// Creates a timer with a given duration time. The function pointer is optional and the function
	// it points to will be called after the timer is expired. If the optional parameter looped is set to true, the timer will
	// be restarted after expiration (until the timer will be deleted with a KillTimer call).
	// Returns the timer identifier, which should be stored, so it is possible to kill/delete the timer with a KillTimer call.
	EV_TimerID CreateTimer(f64 a_DurationInSeconds, bool a_looped = false, void (*a_func) (EV_TimerID ) = nullptr);

	bool KillTimer(EV_TimerID id);			// Kills / Deletes a timer with the given timer identifier.


private:

    // ********************* Elapsed Time
	void	CalculateElapsedTime();

	static const u32 FRAME_SAMPLES_COUNT = 1;
	typedef std::array<f64,FRAME_SAMPLES_COUNT> t_LastFramesArray;
	t_LastFramesArray					m_LastFrameTimeArray;
	t_LastFramesArray::iterator			m_itLastFrame;

    f64 m_ElapsedTimeSeconds;			//!< Elapsed time in seconds of the last frame
	u32 m_LastTimeInMiliseconds;		//!< Last accumulative time in miliseconds


	// ********************* FPS
	void	CalculateFPS();

	f64 m_FramesPerSecond;


    // ********************* Timers

	class EV_TimerInfo
	{
		public:
		EV_TimerInfo(EV_TimerID a_ID, u32 a_CurrentTimeInMiliseconds,f64 a_TotalTimerInSeconds,bool a_looped, void (*a_CallBackFunc)(EV_TimerID id) = nullptr )
		{

					m_ID						= a_ID;
					m_TotalTimeInMiliseconds 	= a_TotalTimerInSeconds * 1000.0;  //Convert to mili-seconds
					m_StartTimeInMilisconds		= a_CurrentTimeInMiliseconds;
					m_EndTimeInMilisconds		= m_StartTimeInMilisconds + m_TotalTimeInMiliseconds;
					m_func						= a_CallBackFunc;
					m_looped 					= a_looped;
					m_ended						= false;
		}

		void Update(u32 a_CurrentTimeInMiliseconds)
		{
			if (!m_ended)
			{
				// Timer ended?
				if ( a_CurrentTimeInMiliseconds > m_EndTimeInMilisconds )
				{
					if (m_func != nullptr)
						m_func(m_ID);
					m_ended = true;
				}
			}
			else
			{


			}

		}

		private:
			EV_TimerInfo();

			EV_TimerID	m_ID;
			u32			m_TotalTimeInMiliseconds;			// Total Ticks that this timer will have to complete. (Delay + total)
			u32			m_StartTimeInMilisconds;			// Start time of the timer
			u32			m_EndTimeInMilisconds;				// End time of the timer
			bool 		m_looped;							// Indicate if the timer will loop
			bool		m_ended;							// Indicate if the timer ended

			void (*m_func) (EV_TimerID id);					// Optional pointer to a function which should be called after the timer is expired



	};


    typedef std::map<EV_TimerID, EV_TimerInfo>		t_TimersInfoMap;
	t_TimersInfoMap								m_TimersMap;

	EV_TimerID									m_CurrentTimerID;

	void UpdateTimers();
};



#endif /* CTIMEMANAGER_H_ */
