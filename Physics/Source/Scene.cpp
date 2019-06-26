#include "Scene.h"

Scene::Scene()
{
	// Create Camera
	GameObject* CameraGO = new GameObject;
	CameraGO->AddComponent(new CameraComponent);
	m_CameraGO = CameraGO;
	m_Camera = CameraGO->GetComponent<CameraComponent>()->GetCamera();
	m_GameObjectManager.AddGameObject(CameraGO);
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