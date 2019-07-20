#include "Scene.h"
#include "Application.h"
Scene::Scene()
{
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
	return &m_GameObjectManager;
}
LightManager* Scene::GetLightManager()
{
	return &m_LightManager;
}
void Scene::SetMouseEnabled(bool b)
{
	Application::SetMouseEnabled(b);
}