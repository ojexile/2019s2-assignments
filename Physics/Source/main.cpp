#include "Application.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

int main(void)
{
	srand((unsigned)time(NULL));
	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
	//_CrtDumpMemoryLeaks();
}