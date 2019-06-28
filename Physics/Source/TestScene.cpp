#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	// Set up camera
	m_CameraGO->GetComponent<TransformComponent>()->setPosition(0, 0, 0);
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
	m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
	// Square
	GameObject* square = m_GameObjectManager.AddGameObject(new GameObject);
	square->GetComponent<TransformComponent>()->setPosition(20, 50, 10);
	square->GetComponent<TransformComponent>()->setScale(2, 2, 1);
	square->GetComponent<TransformComponent>()->setRotation(90, 1, 0, 0);
	square->AddComponent(new RenderComponent(dataContainer->GetMesh("CUBE")));
	//
}