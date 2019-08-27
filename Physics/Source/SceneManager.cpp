#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_CurrentScene = nullptr;
	m_TempScene = nullptr;
	m_bSceneChanged = false;
}

SceneManager::~SceneManager()
{
	DeleteScene();
}

void SceneManager::ChangeScene(Scene* scene)
{
	m_TempScene = scene;
	m_bSceneChanged = true;
}

Scene* SceneManager::GetScene()
{
	return m_CurrentScene;
}

void SceneManager::DeleteScene()
{
	if (m_CurrentScene)
		delete m_CurrentScene;
}
bool SceneManager::IsSceneChanged()
{
	return m_bSceneChanged;
}
void SceneManager::SwapScene()
{
	if (m_CurrentScene)
		delete m_CurrentScene;
	m_CurrentScene = m_TempScene;
	m_CurrentScene->Init();
	m_TempScene = nullptr;
	m_bSceneChanged = false;
}