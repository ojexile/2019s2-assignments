#include "SceneManager.h"

SceneManager::SceneManager()
{
	m_CurrentScene = nullptr;
}

SceneManager::~SceneManager()
{
	DeleteScene();
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