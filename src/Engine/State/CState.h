#ifndef CSTATE_H_
#define CSTATE_H_

#include "Core/CBasicTypes.h"

class CState
{
public:

	virtual void Init() = 0;			// Function will be executed when changing from another state
	virtual void Cleanup() = 0;			// Function will be executed when the state is popped
	virtual void Pause() = 0;			// Function will be executed when another state pushes up / or changes state.
	virtual void Resume() = 0;			// Function will be executed when another state is popped and this is current.

	virtual void Update(f64 dt) = 0;	// Function will be executed when it's the current state

	virtual ~CState();
protected:
	CState() { }
};


#endif /* CSTATE_H_ */
