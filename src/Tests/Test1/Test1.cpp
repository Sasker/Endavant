#include "Core/CCoreEngine.h"

int main ()
{

	CCoreEngine::Instance().StartUp();

	while ( CCoreEngine::Instance().IsRunning() )
	{
		CCoreEngine::Instance().Update();





		CCoreEngine::Instance().Render();
	}

	CCoreEngine::Instance().ShutDown();
	return 0;
}
