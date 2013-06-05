#include "CRefCounter.h"

CRefCounter::CRefCounter() :
	m_Count(1)
{

}

CRefCounter::~CRefCounter()
{

}

void CRefCounter::Grab()
{
	m_Count++;
}

void CRefCounter::Drop()
{
	m_Count--;

	if (m_Count == 0)
	{
		delete this;
	}
}

u32 CRefCounter::GetCount()
{
	return m_Count;
}
