#ifndef CREFCOUNTER_H_
#define CREFCOUNTER_H_

#include "Core/CBasicTypes.h"

class CRefCounter
{
public:
	CRefCounter();
	virtual ~CRefCounter();

	void Grab();
	void Drop();
	uint GetCount();

private:
	uint m_Count;
};

#endif
