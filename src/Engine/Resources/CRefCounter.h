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
	u32 GetCount();

private:
	u32 m_Count;
};

#endif
