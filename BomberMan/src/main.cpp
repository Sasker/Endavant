#include "EVMain.h"
#include "CMainMenuState.h"

int main(int argc, char *argv[])
{
	CCoreEngine &l_core= CCoreEngine::Instance();
	l_core.StartUp();

	CMainMenuState l_mainmenustate;
	l_core.GetStateManager().ChangeState(&l_mainmenustate);

	while ( l_core.IsRunning() )
	{
		l_core.Update();
		l_core.Render();
	}

	l_core.ShutDown();

	return 0;
}



