#include "Application.h"
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#ifdef _WIN32

extern "C" {
	// http://developer.download.nvidia.com/devzone/devcenter/gamegraphics/files/OptimusRenderingPolicies.pdf
	__declspec(dllexport) uint32_t NvOptimusEnablement = 1;

	// https://gpuopen.com/amdpowerxpressrequesthighperformance/
	__declspec(dllexport) uint32_t AmdPowerXpressRequestHighPerformance = 1;
}

#endif // _WIN32
int main(void)
{
	{
		srand((unsigned)time(NULL));
		Application &app = Application::GetInstance();
		app.Init();
		app.Run();
		app.Exit();
		//_CrtDumpMemoryLeaks();
	}
}