#include "Scene.h"
#include "Application.h"
Scene::Scene()
{
}

Scene::~Scene()
{
	/*if (m_CameraGO)
		delete m_CameraGO;*/
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
}