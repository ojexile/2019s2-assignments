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
	m_fLogUpdateTimer = LOG_UPDATE_RATE;
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
	// Window size and position
	WindowData* windowData = WindowData::GetInstance();
	// Font
	CONSOLE_FONT_INFOEX cfi;//CONSOLE_FONT_INFOEX is defined in some windows header
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = (SHORT)windowData->GetFontSize().x;                   // Width of each character in the font
	cfi.dwFontSize.Y = (SHORT)windowData->GetFontSize().y;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(output, FALSE, &cfi);
	//color
	SHORT color = 0x0C;
	SetConsoleTextAttribute(output, color);
	// Hide cursor
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = FALSE;
	ci.dwSize = 10;
	SetConsoleCursorInfo(output, &ci);
	// Console
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) {
		MoveWindow(hwnd, (int)windowData->GetConsolePosition().x, (int)windowData->GetConsolePosition().y
			, (int)windowData->GetConsoleSize().x, (int)windowData->GetConsoleSize().y, TRUE);
	}
}
void Engine::Update(double dt)
{
	SceneManager SceneManager;
	Scene* CurrentScene = SceneManager.GetScene();
	// TODO Update gameobject here
	m_Renderer->Update(dt);
	m_Renderer->Render(CurrentScene);
	// Log
	m_fLogUpdateTimer += (float)dt;
	if (m_fLogUpdateTimer >= LOG_UPDATE_RATE)
	{
		system("cls");
		// Print current logger user
		std::cout << "--------------" << "Current logger user is " << USER_S << "--------------" << std::endl;
		int iYOffset = Locator::GetLogger(Locator::USER).PrintLogs(0);
		Locator::GetLogger(Locator::DEFAULT).PrintLogs(iYOffset);
		m_fLogUpdateTimer = 0;
	}
}
void Engine::Exit()
{
	m_Renderer->Exit();
	delete m_Renderer;
	SceneManager SceneManager;
	SceneManager.DeleteScene();
	DataContainer::DeleteInstance();
}