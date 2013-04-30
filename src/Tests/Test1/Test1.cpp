#include "CCoreEngine.h"

int main ()
{

	CCoreEngine::Instance().StartUp();

	while ( CCoreEngine::Instance().IsRunning() )
	{
		CCoreEngine::Instance().Update();

		//App CODE
		//App CODE
		//App CODE



		CCoreEngine::Instance().Render();
	}

	CCoreEngine::Instance().ShutDown();
	return 0;
}
