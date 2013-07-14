#include "CRenderManager.h"
#include "CWindow.h"
#include "Base_Nodes/CScene.h"
#include "Core/CLogManager.h"

#include "Core/CCoreEngine.h"
#include "Utils/CXMLParserPUGI.h"
#include "Utils/CConversions.h"

// FOR OPENGL DEBUG ONLY
#include "Renderer/GL/CGLError.h"

#include "GLLoad/GLFuncs.h"
#include "GLLoad/gl_core_2_1.h"

static const std::string VIDEO_CONFIG_XML_PATH("./Config/video_options.xml");

CRenderManager::CRenderManager():
m_GLContext(NULL),
m_Window(NULL)
{
	m_SceneStack.reserve(10);
	m_itCurrentScene = m_SceneStack.end();

	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"Object Created!");
}

CRenderManager::~CRenderManager()
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"Object Destroyed!");
}

void	CRenderManager::StartUp()
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"Starting Up! (LOADING VIDEO XML CONFIG)");

	CXMLParserPUGI Parser(VIDEO_CONFIG_XML_PATH);
	int l_WinWidth = Parser.GetIntAttributeValue("WINDOW","WinWidth");
	int l_WinHeight = Parser.GetIntAttributeValue("WINDOW","WinHeight");
	int l_WinPosX = Parser.GetIntAttributeValue("WINDOW","WinPosX");
	int l_WinPosY = Parser.GetIntAttributeValue("WINDOW","WindPosY");

	int l_fullscreen = Parser.GetIntAttributeValue("WINDOW","Fullscreen");

	int l_multisample_buffers = Parser.GetIntAttributeValue("GL_ATTRIBUTES","MultisampleBuffers");
	int l_multisample_samples = Parser.GetIntAttributeValue("GL_ATTRIBUTES","MultisampleSamples");

	std::string l_WindowCaption = Parser.GetStringAttributeValue("WINDOW","WindowCaption");


	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	/* Turn on double buffering with a 24bit Z buffer.
	 * You may need to change this to 16 or 32 for your system */
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);


	//MULTISAMPLE! (ANTIALIASING)
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, l_multisample_buffers);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, l_multisample_samples);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

	m_Window = new CWindow(SDL_WINDOW_OPENGL,l_WindowCaption, l_WinPosX, l_WinPosY, l_WinWidth, l_WinHeight, l_fullscreen != 0 ? true: false );


	CreateGLContext();

	InitGL();

}

const glm::vec2 CRenderManager::GetWindowSize()
{
	return (glm::vec2(m_Window->GetWidth(), m_Window->GetHeight()));
}

void CRenderManager::CreateGLContext()
{
	m_GLContext = SDL_GL_CreateContext(m_Window->GetWindowHandler());

	if (m_GLContext == NULL)
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_VIDEO,"UNABLE TO CREATE GL CONTEXT!");

	//Check Multisamples
	int buffers, samples;
	SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &buffers);
	SDL_GL_GetAttribute( SDL_GL_MULTISAMPLESAMPLES, & samples );
	if ( !buffers || !samples )
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_ERROR, LOGSUB_VIDEO,"NO MSAA");
	else
		CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"ANTIALIASING ON -> MULTISAMPLEBUFFERS: %d   SAMPLES: %d", buffers, samples);

}

void	CRenderManager::InitGL()
{
	// VSYNC OFF
	SDL_GL_SetSwapInterval(0);


	ogl_LoadFunctions();


	// DEBUG OPENGL... not ready yet
	//if (InitGLDebugFunctions())	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"OpenGL Error Checking: ENABLED");


	int l_red, l_green, l_blue, l_alpha;
	SDL_GL_GetAttribute(SDL_GL_RED_SIZE,&l_red);
	SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE,&l_green);
	SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE,&l_blue);
	SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE,&l_alpha);
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"Framebuffer Bytes Info-> R:%d  G:%d  B:%d: A:%d",l_red, l_green, l_blue, l_alpha);



	char *l_vendor = (char*) glGetString(GL_VENDOR);
	char *l_renderer =(char*) glGetString(GL_RENDERER);
	char *l_version = (char*)glGetString(GL_VERSION);
	char *l_glsl = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"Renderer: %s", l_renderer);
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"Vendor: %s", l_vendor);
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"Version: %s", l_version);
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"GLSL: %s", l_glsl);




	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// TODO: Set antialiasing/multisampling
	/*glEnable( GL_MULTISAMPLE );
		glEnable( GL_LINE_SMOOTH );
		glEnable( GL_POLYGON_SMOOTH );
		glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
	 */

	/*set our viewing volume. */
	glViewport( 0, 0, m_Window->GetWidth(), m_Window->GetHeight());


	/* Set our perspective */
	/*
	 * 		________ (width,height)
	 *     |		|
	 *     |		|
	 *     |		|
	 *     |________|
	 *  (0,0)
	 *
	 */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
	glOrtho(0, (GLfloat) m_Window->GetWidth(),	0, (GLfloat) m_Window->GetHeight(),	-1000, 1000);

	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );



}

void	CRenderManager::ResizeWindow(int amplada, int altura)
{
	m_Window->ResizeWindow(amplada, altura);
}

void	CRenderManager::ShutDown()
{
	CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_VIDEO,"ShutDown!  ");
	SDL_GL_DeleteContext(m_GLContext);
	delete m_Window; //TODO Check deletion of window
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void CRenderManager::Render(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if ( m_itCurrentScene != m_SceneStack.end() )
	{
		(*m_itCurrentScene)->Render();
	}

	SDL_GL_SwapWindow(m_Window->GetWindowHandler());

}

void CRenderManager::Update(f64 dt)
{
	if ( m_itCurrentScene != m_SceneStack.end() )
	{
		(*m_itCurrentScene)->Update( dt);
	}
}

void CRenderManager::PushScene(CScene* l_Scene)
{
	m_SceneStack.push_back(l_Scene);

	if (m_SceneStack.size() == 1) //First Scene to be pushed in the stack
		m_itCurrentScene = --m_SceneStack.end(); //Point to it
	else
		++m_itCurrentScene;


}

CScene * const CRenderManager::GetCurrentScene()
{
	return *m_itCurrentScene;
}

void CRenderManager::PopScene()
{
	m_SceneStack.pop_back();

	if (m_SceneStack.empty()) //Last element poped in the stack
		m_itCurrentScene = m_SceneStack.end(); //Point to end()
	else
		--m_itCurrentScene;
}

void CRenderManager::PopToRootScene()
{

}

void CRenderManager::ReplaceScene(CScene* l_Scene)
{
	PopScene();
	PushScene(l_Scene);
}

void CRenderManager::PauseScene()
{

}

void CRenderManager::ResumeScene()
{

}

void CRenderManager::End()
{

	//Erase all the Scenes (don't delete the pointer)
	m_SceneStack.erase(m_SceneStack.begin(),m_SceneStack.end());
	m_itCurrentScene = m_SceneStack.end();

}

