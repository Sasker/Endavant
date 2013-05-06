#ifndef ISUBSYSTEM_H_
#define ISUBSYSTEM_H_
#include "CBasicTypes.h"

class ISubSystem
{
public:
	virtual ~ISubSystem() { }

	virtual void StartUp(void) = 0;
	virtual void ShutDown(void) = 0;
	virtual void Update(f64 dt) = 0;
};

#endif
