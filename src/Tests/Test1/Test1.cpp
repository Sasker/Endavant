#include "Core/CCoreEngine.h"
#include "Input/CInputManager.h"
#include "Input/CInputMouse.h"
#include "Core/CLogManager.h"
#include "Renderer/Base_Nodes/CScene.h"
#include "Renderer/Draw_Nodes/CRectangle.h"
#include "Renderer/Draw_Nodes/CTriangle.h"

int main(int argc, char *argv[])
{

	CCoreEngine &l_core= CCoreEngine::Instance();
	l_core.StartUp();

	auto	&l_input = CCoreEngine::Instance().GetInputManager();
	auto	&l_log = CCoreEngine::Instance().GetLogManager();
	auto	&l_render = CCoreEngine::Instance().GetRenderManager();


	l_input.GetMouse().InsertButtonAction("PutaMare", "MOUSE_LB");

    CScene MiEscena;
    CTriangle MiTriangulo( glm::vec2( 0, 100), glm::vec2( -100, 0), glm::vec2( 100, 0), 0, glm::vec3(1.0,0.0,0.0) );
    CTriangle MiTriangulo2( glm::vec2( -100, 100), glm::vec2( 100, 100), glm::vec2( 0, 0), 1, glm::vec3(1.0,0.0,1.0) );
    CRectangle Rectangle(  glm::vec2( 100, 100), 11,glm::vec3(1.0,0.0,0.0) );
    CRectangle Rectangle2(  glm::vec2( 100, 100), 12,glm::vec3(0.0,1.0,0.0) );

    MiTriangulo.SetPosition( glm::vec2( 100, 100) );
    MiTriangulo2.SetPosition( glm::vec2( 200, 200) );

    MiEscena.SetPosition(glm::vec2(100,100));

    MiEscena.AddChild( &Rectangle );
    MiEscena.AddChild( &Rectangle2 );



	l_render.PushScene(&MiEscena);

	while ( l_core.IsRunning() )
	{
		l_core.Update();

		if (l_input.GetMouse().IsActionActive("PutaMare") || l_input.GetMouse().IsButtonPressed(MOUSE_MB))
			l_log.LogOutput( LOG_INFO, LOGSUB_GAME ,"YESSSSS");


		l_core.Render();
	}

	l_core.ShutDown();

	return 0;
}

