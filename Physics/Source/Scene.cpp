#include "Scene.h"
#include "Application.h"
Scene::Scene()
{
	m_bCursorEnabled = false;
}

Scene::~Scene()
{
}
GameObject* Scene::GetCameraGameObject()
{
	return m_CameraGO;
}
Camera* Scene::GetCamera()
{
	return m_Camera;
}
GameObjectManager* Scene::GetGameObjectManager()
{
	return &m_GOM;
}
LightManager* Scene::GetLightManager()
{
	return &m_LightManager;
}
void Scene::SetCursorEnabled(bool b)
{
	Application::SetCursorEnabled(b);
	m_bCursorEnabled = b;
}
GameObject* Scene::GetGO(std::string s)
{
	return DataContainer::GetInstance()->GetGameObject(s);
}
bool Scene::GetCursorEnabled()
{
	return m_bCursorEnabled;
}