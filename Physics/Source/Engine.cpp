#include "Engine.h"

// Select Debug logger user
// Users are enums located in locator.h
#define USER CHENG

#define TO_STR2(x) #x
#define TO_STR(x) TO_STR2(x)
#define USER_S ( TO_STR(USER) )

Renderer* Engine::m_Renderer;

Engine::Engine()
{
	m_Renderer = new RenderingManager;
}

Engine::~Engine()
{
}

void Engine::Init()
{
	m_Renderer->Init();
	// Init first scene
	SceneManager SceneManager;
	SceneManager.ChangeScene(new TestScene);
	// Window settings
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	// Hide cursor
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = false;
	ci.dwSize = 0;
	SetConsoleCursorInfo(output, &ci);
	// Window size and position
	WindowData* windowData = WindowData::GetInstance();
	// Console
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) {
		MoveWindow(hwnd, (int)windowData->GetConsolePosition().x, (int)windowData->GetConsolePosition().y
			, (int)windowData->GetConsoleSize().x, (int)windowData->GetConsoleSize().y, TRUE);
	}
	// Font
	CONSOLE_FONT_INFOEX font;//CONSOLE_FONT_INFOEX is defined in some windows header
	GetCurrentConsoleFontEx(output, false, &font);//PCONSOLE_FONT_INFOEX is the same as CONSOLE_FONT_INFOEX*
	font.dwFontSize.X = (SHORT)windowData->GetFontSize().x;
	font.dwFontSize.Y = (SHORT)windowData->GetFontSize().y;
	SetCurrentConsoleFontEx(output, false, &font);
	//color
	SHORT color = 0x0C;
	SetConsoleTextAttribute(output, color);
	// Print current logger user
	std::cout << "--------------" << "Current logger user is " << USER_S << "--------------" << std::endl;
}
void Engine::Update(double dt)
{
	SceneManager SceneManager;
	Scene* CurrentScene = SceneManager.GetScene();
	// TODO Update gameobject here
	m_Renderer->Update(dt);
	m_Renderer->Render(CurrentScene);
	// Log
	int iYOffset = Locator::GetLogger(Locator::USER).PrintLogs(0);
	Locator::GetLogger(Locator::DEFAULT).PrintLogs(iYOffset);
}
void Engine::Exit()
{
	m_Renderer->Exit();
	delete m_Renderer;
	SceneManager SceneManager;
	SceneManager.DeleteScene();
	DataContainer::DeleteInstance();
}