#ifndef CSTATE_H_
#define CSTATE_H_

#include "Core/CBasicTypes.h"

class CState
{
public:

	virtual void Init() = 0;
	virtual void Cleanup() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void Update(f64 dt) = 0;

	virtual ~CState(){};
protected:
	CState(){};
};


#endif /* CSTATE_H_ */
