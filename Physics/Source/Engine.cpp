#include "Engine.h"
#include "KeyboardManager.h"
#include "Time.h"
#include "AudioManager.h"
#include "Preferences.h"
#include "Resources.h"
#include "Utility.h"
#include "DataContainer.h"
#include "ObserverComponent.h"
#include "GenericSubject.h"
#include "StopWatch.h"
#include "MyMath.h"
#include "WorldValues.h"
#include "InputManager.h"
#include "MouseManager.h"
#include "EntityLibrary.h"
// Start Scene
#include "DefaultScene.h"
#include "MainMenu.h"
#include "LoginScene.h"
RenderingManager* Engine::m_Renderer;
#define TIMINGS false

#define SCENE DefaultScene

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
	Math::InitRNG();
	DataContainer::GetInstance()->Init();
	AudioManager* audio = AudioManager::GetInstance();
	audio->Play3D("pop.wav", {});
	m_frameCount = 0;
	m_Renderer->Init();
	// Init first scene
	SceneManager* SceneManager = SceneManager::GetInstance();
	SceneManager->ChangeScene(new SCENE());
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
	m_frameCount++;
	SceneManager* SceneManager = SceneManager::GetInstance();
	if (SceneManager->IsSceneChanged())
		SceneManager->SwapScene();
	Scene* CurrentScene = SceneManager->GetScene();
	// Update time
	Time::GetInstance()->Update(dt);
	StopWatch sMain(true);
	StopWatch s(true);
	// Update gameobject here
	GameObjectManager* GOM = CurrentScene->GetGameObjectManager();
	std::vector<GameObject*> GOObserverList;
	std::map<std::string, LayerData*>::iterator it;
	int counter = 0;
	for (it = GOM->GetLayerList()->begin(); it != GOM->GetLayerList()->end(); it++)
	{
		// it->first == key
		// it->second == value,
		std::vector<GameObject*>* GOList = it->second->GetGOList();
		for (unsigned i = 0; i < GOList->size(); ++i)
		{
			GameObject* go = GOList->at(i);
			if (!go)
			{
				DEFAULT_LOG("GO IS UNITIALISED.");
				continue;
			}
			if (!go->IsActive())
				continue;
			StopWatch s(true);
			go->Update(min(dt * WorldValues::TimeScale, 0.1));
			if (TIMINGS)
			{
				if (s.Stop()->GetTime() > 0.01f)
					CHENG_LOG("GO update longer than 0.01s: ", STOP_S);
			}
			CheckGOForObserver(go, &GOObserverList);
			counter++;
		}
	}
	if (TIMINGS)
		CHENG_LOG("Time to update: ", STOP_S);
	s.Reset();
	//Update coll-------------------------------------------------------------------------------
	StopWatch sw(true);
	m_CollisionManager.Update(CurrentScene->GetGameObjectManager(), (m_frameCount & 255));
	if (TIMINGS)
		CHENG_LOG("Time to check collision: ", STOP_S);
	s.Reset();
	sw.Stop();
	KZ_LOG("[Collision_Time_2]", " CollisionManager.Update() took " + sw.GetSTime() + "s");
	// Update Observers
	GenericSubject::GetInstance()->NotifyObservers(&GOObserverList);
	// Remove to be destroyed--------------------------------------------------------------------------------
	GOM->DestroyQueued();
	//--------------------------------------------------------------------------------
	m_Renderer->Update(dt);
	m_Renderer->Render(CurrentScene);
	if (TIMINGS)
		CHENG_LOG("Time to render: ", STOP_S);
	if (TIMINGS)
		CHENG_LOG("Time for loop: ", sMain.Stop()->GetSTime());
	// Log================================================================================
	m_fLogUpdateTimer += (float)dt;
	float fLogUpdateRate = std::stof(Preferences::GetPref(Resources::PreferencesTerm::LogUpdateRate));
	if (m_fLogUpdateTimer >= fLogUpdateRate && fLogUpdateRate >= 0)
	{
		// Set top left
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coord;
		coord.X = 0;
		coord.Y = 0;
		SetConsoleCursorPosition(handle, coord);
		//
		// Print current logger user
		std::string sLogUser = Preferences::GetPref(Resources::PreferencesTerm::LogUser);
		Locator::eLoggerUsers eLoggerUser = StringToUser(sLogUser);
		std::cout << "--------------" << "Current logger user is " << sLogUser << "--------------" << std::endl;
		switch (eLoggerUser)
		{
		case Locator::ALL:
		{
			Locator::eLoggerUsers eCurrentUser = Locator::DEFAULT;
			while (eCurrentUser != Locator::eLoggerUsers::ALL)
			{
				Locator::GetLogger(eCurrentUser).PrintLogs();
				eCurrentUser = static_cast<Locator::eLoggerUsers>(eCurrentUser + 1);
			}
		}
		break;
		default:
			Locator::GetLogger(Locator::DEFAULT).PrintLogs();
			Locator::GetLogger(eLoggerUser).PrintLogs();
			break;
		}
		m_fLogUpdateTimer = 0;
	}
}
void Engine::CheckGOForObserver(GameObject* go, std::vector<GameObject*>* GOList)
{
	if (go->GetComponent<ObserverComponent>(true))
	{
		GOList->push_back(go);
	}
	for (unsigned i = 0; i < go->GetChildList()->size(); ++i)
	{
		GameObject* GOChild = go->GetChildList()->at(i);
		CheckGOForObserver(GOChild, GOList);
	}
}
RenderingManagerBase * Engine::GetRenderManager()
{
	return m_Renderer;
}
void Engine::Exit()
{
	m_Renderer->Exit();
	delete m_Renderer;
	SceneManager::DeleteInstance();
	DataContainer::DeleteInstance();
	InputManager::DeleteInstance();
	KeyboardManager::DeleteInstance();
	MouseManager::DeleteInstance();
	AudioManager::DeleteInstance();
	Preferences::Clear();
	Time::DeleteInstance();
	GenericSubject::DeleteInstance();
	EntityLibrary::DeleteInstance();
}