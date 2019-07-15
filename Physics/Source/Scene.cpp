#include "Scene.h"

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