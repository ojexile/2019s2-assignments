#include "Application.h"
#include "MemoryLeak.h"
#include <cstdlib>
#include <time.h>

int main( void )
{
	srand((unsigned)time(NULL));
	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
	isMemLeaked();
}