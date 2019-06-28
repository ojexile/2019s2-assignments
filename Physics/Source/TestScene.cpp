#include "TestScene.h"
#include "PlayerScript.h"

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
	m_CameraGO->GetComponent<TransformComponent>()->SetPosition(0, 0, 0);
	m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_FIRST);
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);
	// Square
	GameObject* square = m_GameObjectManager.AddGameObject();
	//square->GetComponent<TransformComponent>()->setPosition(20, 50, 10);
	square->GetComponent<TransformComponent>()->SetPosition(0, 0, -50);
	square->GetComponent<TransformComponent>()->SetScale(2, 2, 1);
	square->GetComponent<TransformComponent>()->SetRotation(90, 1, 0, 0);
	square->AddComponent(new RenderComponent(dataContainer->GetMesh("CUBE")));
	//

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->AddComponent(new PlayerScript);
	player->AddChild(m_CameraGO);
}