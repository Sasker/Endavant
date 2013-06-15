#include "Core/CCoreEngine.h"
#include "Input/CInputManager.h"
#include "Input/CInputMouse.h"
#include "Core/CLogManager.h"

int main(int argc, char *argv[])
{

	CCoreEngine &l_core= CCoreEngine::Instance();

	l_core.StartUp();
	CInputManager &l_input = CCoreEngine::Instance().GetInputManager();
	CLogManager	&l_log = CCoreEngine::Instance().GetLogManager();

	l_input.GetMouse().InsertButtonAction("PutaMare", "MOUSE_LB");

	while ( l_core.IsRunning() )
	{
		l_core.Update();

		if (l_input.GetMouse().IsActionActive("PutaMare")
				|| l_input.GetMouse().IsButtonPressed(MOUSE_MB)
		)

		{
			l_log.LogOutput( LOG_INFO, LOGSUB_GAME ,"YESSSSS");

		}



		l_core.Render();
	}

	l_core.ShutDown();

	return 0;
}
