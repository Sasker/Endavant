#include "EVMain.h"

int main(int argc, char *argv[])
{
	CCoreEngine &l_core= CCoreEngine::Instance();
	l_core.StartUp();

	while ( l_core.IsRunning() )
	{
		// Actualitzo l'engine
		l_core.Update();


		// Actualitzo els jugadors

		// Pinto
		l_core.Render();
	}

	l_core.ShutDown();

	return 0;
}



