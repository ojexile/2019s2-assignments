#include "SceneManager.h"
Scene* SceneManager::m_CurrentScene;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::ChangeScene(Scene* scene)
{
	this->DeleteScene();
	m_CurrentScene = scene;
	scene->Init();
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