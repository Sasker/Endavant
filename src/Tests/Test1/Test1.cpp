#include "Core/CCoreEngine.h"
#include "Input/CInputManager.h"
#include "Input/CInputMouse.h"
#include "Core/CLogManager.h"

int main(int argc, char *argv[])
{

	CCoreEngine::Instance().StartUp();


	CCoreEngine::Instance().GetInputManager().GetMouse().InsertButtonAction("PutaMare", "MOUSE_LB");

	while ( CCoreEngine::Instance().IsRunning() )
	{
		CCoreEngine::Instance().Update();

		if ( CCoreEngine::Instance().GetInputManager().GetMouse().IsActionActive("PutaMare")
				|| CCoreEngine::Instance().GetInputManager().GetMouse().IsButtonPressed(MOUSE_MB)
		)

		{
			CCoreEngine::Instance().GetLogManager().LogOutput( LOG_INFO, LOGSUB_GAME ,"YESSSSS");

		}



		CCoreEngine::Instance().Render();
	}

	CCoreEngine::Instance().ShutDown();

	return 0;
}
