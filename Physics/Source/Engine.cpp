#include "Engine.h"

#define USER CHENG

#define TO_STR2(x) #x
#define TO_STR(x) TO_STR2(x)
#define USER_S ( TO_STR(CHENG) )

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
	if (hwnd != NULL) { MoveWindow(hwnd, 960, 0, 960, 1020, TRUE); }

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