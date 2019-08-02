#include "Engine.h"
#include "KeyboardManager.h"
#include "Time.h"
#include "Preferences.h"
#include "Resources.h"
#include "Utility.h"
#include "AudioManager.h"
// Select Debug logger user
// Users are enums located in locator.h
//#define USER CHENG
//
//#define TO_STR2(x) #x
//#define TO_STR(x) TO_STR2(x)
//#define USER_S ( TO_STR(USER) )

Renderer* Engine::m_Renderer;

Engine::Engine()
{
	m_Renderer = new RenderingManager;
	m_fLogUpdateTimer = std::stof(Preferences::GetPref(Resources::PreferencesTerm::LogUpdateRate));
	m_fLogUpdateTimer = 0;
}

Engine::~Engine()
{
}

void Engine::Init()
{
	m_Renderer->Init();
	// Init first scene
	SceneManager* SceneManager = SceneManager::GetInstance();
	SceneManager->ChangeScene(new TestScene);
	// Window settings
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	// Window size and position
	Vector3 ConsoleSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::ConsoleSize));
	Vector3 FontSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::FontSize));
	Vector3 ConsolePos = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::ConsolePosition));
	// Font

	CONSOLE_FONT_INFOEX cfi;//CONSOLE_FONT_INFOEX is defined in some windows header
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = (SHORT)FontSize.x;                   // Width of each character in the font
	cfi.dwFontSize.Y = (SHORT)FontSize.y;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	//std::wcscpy(cfi.FaceName, L"Consolas"); // Choose your font
	SetCurrentConsoleFontEx(output, FALSE, &cfi);
	//color
	SHORT color = 0x0F;
	SetConsoleTextAttribute(output, color);
	// Hide cursor
	CONSOLE_CURSOR_INFO ci;
	ci.bVisible = FALSE;
	ci.dwSize = 10;
	SetConsoleCursorInfo(output, &ci);
	// Console
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) {
		MoveWindow(hwnd, (int)ConsolePos.x, (int)ConsolePos.y
			, (int)ConsoleSize.x, (int)ConsoleSize.y, TRUE);
	}
}
void Engine::SetMouseCallback(GLFWwindow* window)
{
	m_Renderer->SetMouseCallback(window);
}
void Engine::Update(double dt)
{
	SceneManager* SceneManager = SceneManager::GetInstance();
	if (SceneManager->IsSceneChanged())
		SceneManager->SwapScene();
	Scene* CurrentScene = SceneManager->GetScene();
	// Update time
	Time::GetInstance()->Update(dt);
	// Update gameobject here
	GameObjectManager* GOM = CurrentScene->GetGameObjectManager();
	std::map<std::string, LayerData*>::iterator it;
	for (it = GOM->GetLayerList()->begin(); it != GOM->GetLayerList()->end(); it++)
	{
		// it->first == key
		// it->second == value,
		std::vector<GameObject*>* GOList = it->second->GetGOList();
		for (unsigned i = 0; i < GOList->size(); ++i)
		{
			if (!GOList->at(i)->IsActive())
				continue;
			GOList->at(i)->Update(dt);
		}
	}

	m_Renderer->Update(dt);
	m_Renderer->Render(CurrentScene);
	// Log
	m_fLogUpdateTimer += (float)dt;
	//CHENG_LOG("CHENG");
	//RYAN_LOG("RYAN");
	//KZ_LOG("KZ");
	//LZ_LOG("LZ");
	float fLogUpdateRate = std::stof(Preferences::GetPref(Resources::PreferencesTerm::LogUpdateRate));
	if (m_fLogUpdateTimer >= fLogUpdateRate && fLogUpdateRate > 0)
	{
		system("cls");
		// Print current logger user
		std::string sLogUser = Preferences::GetPref(Resources::PreferencesTerm::LogUser);
		Locator::eLoggerUsers eLoggerUser = StringToUser(sLogUser);
		std::cout << "--------------" << "Current logger user is " << sLogUser << "--------------" << std::endl;
		int iYOffset = 0;
		switch (eLoggerUser)
		{
		case Locator::ALL:
		{
			Locator::eLoggerUsers eCurrentUser = Locator::DEFAULT;
			while (eCurrentUser != Locator::eLoggerUsers::ALL)
			{
				iYOffset = Locator::GetLogger(eCurrentUser).PrintLogs(iYOffset);
				eCurrentUser = static_cast<Locator::eLoggerUsers>(eCurrentUser + 1);
			}
		}
		break;
		default:
			iYOffset = Locator::GetLogger(Locator::DEFAULT).PrintLogs(iYOffset);
			Locator::GetLogger(eLoggerUser).PrintLogs(iYOffset);
			break;
		}
		m_fLogUpdateTimer = 0;
	}
}
void Engine::Exit()
{
	m_Renderer->Exit();
	delete m_Renderer;
	SceneManager::DeleteInstance();
	DataContainer::DeleteInstance();
	KeyboardManager::DeleteInstance();
	AudioManager::DeleteInstance();
	Preferences::Clear();
	Time::DeleteInstance();
}