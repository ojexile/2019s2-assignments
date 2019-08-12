#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "Engine.h"
#include "Preferences.h"
class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static void GetCursorPos(double *xpos, double *ypos);
	static int GetWindowWidth();
	static int GetWindowHeight();
	static void GetScrollWheelPos(double* xpos, double* ypos);
	static void SetCursorEnabled(bool);
private:
	Application();
	~Application();

	//Declare a window object
	Timer m_timer;

	Engine* m_Engine;
};

#endif