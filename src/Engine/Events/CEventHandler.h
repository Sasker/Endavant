#ifndef CEVENTHANDLER_H_
#define CEVENTHANDLER_H_

#include <set>
#include <map>
#include <SDL2/SDL.h>

class CEventHandler
{
public:
	typedef std::set< Uint32 > 				t_CodeList;
	typedef std::map< Uint32, t_CodeList > 	t_TypeList;

	CEventHandler();
	virtual ~CEventHandler();

	virtual void HandleEvent(Uint32 a_Type, Uint32 a_Code, SDL_Event* a_Event = NULL) = 0;

	void AddEvent(Uint32 a_Type, Uint32 a_Code);

	void RegisterEventManager();
	void UnRegisterEventManager();

private:


	t_TypeList m_TypeList;
	bool m_Registered;

};

#endif /* CEVENTHANDLER_H_ */
