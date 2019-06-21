#include "Application.h"
#include "MemoryLeak.h"

int main( void )
{
	Application &app = Application::GetInstance();
	app.Init();
	app.Run();
	app.Exit();
	isMemLeaked();
}