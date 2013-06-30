#include "Core/CCoreEngine.h"
#include "Input/CInputManager.h"
#include "Input/CInputMouse.h"
#include "Core/CLogManager.h"
#include "Time/CTimeManager.h"
#include "Renderer/Base_Nodes/CScene.h"
#include "Renderer/Draw_Nodes/CRectangle.h"
#include "Renderer/Draw_Nodes/CTriangle.h"
#include "Renderer/Draw_Nodes/CSprite.h"


#include "PongPlayer.h"

int main(int argc, char *argv[])
{

	CCoreEngine &l_core= CCoreEngine::Instance();
	l_core.StartUp();

	auto	&l_input = CCoreEngine::Instance().GetInputManager();
	//auto	&l_log = CCoreEngine::Instance().GetLogManager();
	auto	&l_render = CCoreEngine::Instance().GetRenderManager();
	auto	&l_timer = CCoreEngine::Instance().GetTimerManager();



	//Escena principal
    CScene MiEscena;
    MiEscena.SetPosition(glm::vec2(0,0));
	l_render.PushScene(&MiEscena);


	//Jugadors
	l_input.GetKeyboard().InsertKeyAction("P1Up", "O");
	l_input.GetKeyboard().InsertKeyAction("P1Down", "L");
	PongPlayer	l_jugador1(glm::vec2(100, l_render.GetWindowSize().y / 2), "P1Up", "P1Down");

	l_input.GetKeyboard().InsertKeyAction("P2Up", "Q");
	l_input.GetKeyboard().InsertKeyAction("P2Down", "A");
	PongPlayer	l_jugador2(glm::vec2(l_render.GetWindowSize().x - 100, l_render.GetWindowSize().y / 2),"P2Up", "P2Down");

	CTriangle	testtriangle(glm::vec2(100,0), glm::vec2(50,50),glm::vec2(0,0),12,glm::vec3(1,0,0) );
	CCoreEngine::Instance().GetRenderManager().GetCurrentScene()->AddChild(&testtriangle);

	CSprite		testsprite;
	CCoreEngine::Instance().GetRenderManager().GetCurrentScene()->AddChild(&testsprite);
	testsprite.InitSprite("exemple.bmp");
	testsprite.SetPosition(glm::vec2(300,300));
	testsprite.SetSpriteCurrentSize(glm::uvec2(25,25));




	while ( l_core.IsRunning() )
	{
		// Actualitzo l'engine
		l_core.Update();


		// Actualitzo els jugadors
		auto dt = l_timer.GetElapsedTime();
		l_jugador1.Update(dt);
		l_jugador2.Update(dt);

		// Pinto
		l_core.Render();
	}

	l_core.ShutDown();

	return 0;
}

