#include "CCoreEngine.h"
//Forward declaration includes
#include "Renderer/CRenderManager.h"
#include "Input/CInputManager.h"
#include "CLogManager.h"
#include "Time/CTimeManager.h"
#include "Events/CEventManager.h"
#include "Resources/CResourceManager.h"
#include "Sound/CSoundManager.h"

//
#include <SDL2/SDL.h>
#include "Defines.h"

CCoreEngine::CCoreEngine():
m_run(false),
m_rendermngr(NULL),
m_inputmngr(NULL),
m_logmngr(NULL),
//m_soundmngr(NULL),
m_timermngr(NULL),
m_eventmngr(NULL),
m_resourcemngr(NULL),
m_soundmngr(NULL)
{

}

CCoreEngine::~CCoreEngine()
{
	delete m_timermngr;
	//delete m_game;
	delete m_rendermngr;
	delete m_inputmngr;
	delete m_logmngr;
	delete m_eventmngr;
	delete m_resourcemngr;
	delete m_soundmngr;
}

//Singleton
CCoreEngine &CCoreEngine::Instance()
{
	static CCoreEngine instance;
	return instance;
}

CLogManager		&CCoreEngine::GetLogManager()
{
	return *m_logmngr;
}
CRenderManager	&CCoreEngine::GetRenderManager()
{
	return *m_rendermngr;
}
CTimeManager	&CCoreEngine::GetTimerManager()
{
	return *m_timermngr;
}
CInputManager	&CCoreEngine::GetInputManager()
{
	return *m_inputmngr;
}

CEventManager	&CCoreEngine::GetEventManager()
{
	return *m_eventmngr;
}

CResourceManager &CCoreEngine::GetResourceManager()
{
	return *m_resourcemngr;
}

CSoundManager &CCoreEngine::GetSoundManager()
{
	return *m_soundmngr;
}

bool CCoreEngine::IsRunning()
{
	return m_run;
}

void CCoreEngine::StopCore()
{
	m_run = false;
}

bool	CCoreEngine::StartUpSDL()
{
	SDL_version compiled;
	SDL_version linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);

	std::cout<<"We compiled against SDL version: "<< (uint) compiled.major<<"."<<(uint) compiled.minor<<"."<<(uint) compiled.patch<<std::endl;
	std::cout<<"And we are linking against SDL version: "<< (uint) linked.major<<"."<<(uint) linked.minor<<"."<<(uint) linked.patch<<std::endl;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) != 0)
	{
		std::cout<<"ERROR! Unable to initialize SDL: "<<SDL_GetError();
		return false;
    }
	return true;
}

void	CCoreEngine::StartUp()
{
	if (!StartUpSDL())
		return;

	//CREO ELS SUBSISTEMES EN ORDRE
	m_logmngr = new CLogManager();
	m_logmngr->StartUp();

	m_rendermngr = new CRenderManager();
	m_rendermngr->StartUp();

	m_soundmngr = new CSoundManager();
	m_soundmngr->StartUp();

	m_resourcemngr = new CResourceManager();
	m_resourcemngr->StartUp();

	//m_soundmngr = new SoundManager();
	//m_soundmngr->StartUp();

	m_eventmngr = new CEventManager;
	m_eventmngr->StartUp();

	m_inputmngr = new CInputManager();
	m_inputmngr->StartUp();

	m_timermngr = new CTimeManager();
	m_timermngr->StartUp();

	m_logmngr->LogOutput( LOG_INFO, LOGSUB_ENGINE,"Start all subsystems OK");
	m_run = true;
}

void	CCoreEngine::Update()
{
	if (m_run)
	{
		// UPDATES
		float dt = 0.0F;
		m_timermngr->Update(dt);
		dt = m_timermngr->GetElapsedTime();


		m_inputmngr->Update(dt);
		m_eventmngr->Update(dt);
		m_soundmngr->Update(dt);
		m_resourcemngr->Update(dt);

		m_rendermngr->Update(dt);

	}
}

void CCoreEngine::Render()
{
	if (m_run)
	{
		m_rendermngr->Render(); //Renders
	}
}

void	CCoreEngine::ShutDown()
{
	//EN ORDRE INVERS AL DE CREACIO
	m_logmngr->LogOutput( LOG_INFO, LOGSUB_ENGINE,"ShutDown all subsystems:  ");
	m_timermngr->ShutDown();
	m_inputmngr->ShutDown();
	m_eventmngr->ShutDown();
	m_resourcemngr->ShutDown();
	m_soundmngr->ShutDown();
	m_rendermngr->ShutDown();
	m_logmngr->ShutDown();

	SDL_Quit();

}
