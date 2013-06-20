#include "Core/CCoreEngine.h"
#include "Input/CInputManager.h"
#include "Input/CInputMouse.h"
#include "Core/CLogManager.h"
#include "Time/CTimeManager.h"
#include "Renderer/Base_Nodes/CScene.h"
#include "Renderer/Draw_Nodes/CRectangle.h"
#include "Renderer/Draw_Nodes/CTriangle.h"


#include "PongPlayer.h"

int main(int argc, char *argv[])
{

	CCoreEngine &l_core= CCoreEngine::Instance();
	l_core.StartUp();

	auto	&l_input = CCoreEngine::Instance().GetInputManager();
	//auto	&l_log = CCoreEngine::Instance().GetLogManager();
	auto	&l_render = CCoreEngine::Instance().GetRenderManager();
	auto	&l_timer = CCoreEngine::Instance().GetTimerManager();

	l_input.GetMouse().InsertButtonAction("PutaMare", "MOUSE_LB");

	//Escena principal
    CScene MiEscena;
    MiEscena.SetPosition(glm::vec2(0,0));
	l_render.PushScene(&MiEscena);


	//Jugadors
	PongPlayer	l_jugador1;


	PongPlayer	l_jugador2;





	while ( l_core.IsRunning() )
	{
		// Actualitzo l'engine
		l_core.Update();


		// Actualitzo els jugadors
		auto dt = l_timer.GetElapsedTime();
		l_jugador1.Update(dt);
		//l_jugador2.Update(dt);

		// Pinto
		l_core.Render();
	}

	l_core.ShutDown();

	return 0;
}

