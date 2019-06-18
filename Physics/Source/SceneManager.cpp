#include "SceneManager.h"
Scene* SceneManager::m_CurrentScene;

SceneManager::SceneManager()
{
	// Init first scene
	m_CurrentScene = new TestScene;
	m_CurrentScene->Init();
}

SceneManager::~SceneManager()
{
	delete m_CurrentScene;
}

void SceneManager::ChangeScene(Scene* scene)
{
	if (m_CurrentScene)
		delete m_CurrentScene;
	m_CurrentScene = scene;
}

Scene* SceneManager::GetScene()
{
	return m_CurrentScene;
}