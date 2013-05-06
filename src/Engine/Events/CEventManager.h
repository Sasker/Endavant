#ifndef CEVENTMANAGER_H_
#define CEVENTMANAGER_H_

#include <set>
#include <map>
#include <list>
#include <SDL2/SDL.h>
#include "Core/ISubSystem.h"
#include "CEventHandler.h"

class CEventManager : public ISubSystem
{
public:
	typedef std::set< CEventHandler* > 				t_ListenersGroup;
	typedef std::map< Uint32, t_ListenersGroup > 	t_ListenersCode;
	typedef std::map< Uint32, t_ListenersCode >		t_Listeners;

	~CEventManager();

	// ISubSystem
	void StartUp(void);
	void ShutDown(void);
	void Update(f64 dt);

	void Register(const CEventHandler::t_TypeList& a_TypeList, CEventHandler* a_Listener);
	void UnRegister(const CEventHandler::t_TypeList& a_TypeList, CEventHandler* a_Listener);

	void PushEvent(Uint32 a_Type, Uint32 a_Code);

private:
	friend class CCoreEngine;
	CEventManager();

	t_Listeners m_Listeners;
};

#endif /* CEVENTMANAGER_H_ */
