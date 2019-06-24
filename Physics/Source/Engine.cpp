#include "Engine.h"

#define USER CHENG
#define USER_S "CHENG"

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

	// Console
	HWND hwnd = GetConsoleWindow();
	if (hwnd != NULL) { MoveWindow(hwnd, 900, 0, 1000, 1000, TRUE); }

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
	Locator::GetLogger(Locator::USER).PrintLogs();
}
void Engine::Exit()
{
	m_Renderer->Exit();
	delete m_Renderer;
	SceneManager SceneManager;
	SceneManager.DeleteScene();
	DataContainer::DeleteInstance();
}