#ifndef ISUBSYSTEM_H_
#define ISUBSYSTEM_H_

class ISubSystem
{
public:
	virtual ~ISubSystem() { }

	virtual void StartUp(void) = 0;
	virtual void ShutDown(void) = 0;
	virtual void Update(float dt) = 0;
};

#endif
