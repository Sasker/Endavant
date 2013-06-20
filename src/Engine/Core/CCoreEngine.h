#ifndef CCOREENGINE_H_
#define CCOREENGINE_H_

#include "Defines.h"

#include "Renderer/CRenderManager.h"
#include "Input/CInputManager.h"
#include "Core/CLogManager.h"
#include "Time/CTimeManager.h"
#include "Events/CEventManager.h"
#include "Resources/CResourceManager.h"
#include "Sound/CSoundManager.h"

class CCoreEngine {
public:
	void	StartUp();
	void	ShutDown();
	void	Update();
	void	Render();

	static CCoreEngine &Instance();

	CRenderManager		&GetRenderManager(); //retorna la direccio del VideoManager
	CInputManager		&GetInputManager(); //retorna la direccio de l'inputmanager
	CLogManager			&GetLogManager(); 	//retorna la direccio del LogManager
	CTimeManager		&GetTimerManager(); //Retorna la direccio del Timer
	CEventManager		&GetEventManager();	//Retorna la direccio del gestor d'events
	CResourceManager	&GetResourceManager(); //Retorna la direccio del gestor de recursos
	CSoundManager		&GetSoundManager(); ////Retorna la direccio del manager d'audio

	bool	IsRunning();
	void	StopCore();

	~CCoreEngine();
private:

	bool	m_run; 						//Flag de funcionament de l'Engine
	CCoreEngine();


	CRenderManager		*m_rendermngr;
	CInputManager 		*m_inputmngr;
	CLogManager	 		*m_logmngr;
	CTimeManager		*m_timermngr;
	CEventManager		*m_eventmngr;
	CResourceManager 	*m_resourcemngr;
	CSoundManager		*m_soundmngr;

	bool	StartUpSDL();
};

#endif /* CCOREENGINE_H_ */
