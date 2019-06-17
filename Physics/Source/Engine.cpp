#include "Engine.h"

Renderer* Engine::m_Renderer;

Engine::Engine()
{
	CurrentScene = new TestScene;
	CurrentScene->Init();
}

Engine::~Engine()
{
}

void Engine::Init()
{
	m_Renderer = new RenderingManager;
	m_Renderer->Init();
}
void Engine::Update(double dt)
{
	// TODO Update gameobject here
	m_Renderer->Update(dt);
	m_Renderer->Render(CurrentScene);
}
void Engine::Exit()
{
	delete m_Renderer;
}