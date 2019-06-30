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
	GameObject* cube = m_GameObjectManager.AddGameObject();
	cube->GetComponent<TransformComponent>()->SetPosition(0, 10, 0);
	cube->GetComponent<TransformComponent>()->SetScale(1, 1, 1);
	cube->GetComponent<TransformComponent>()->SetRotation(90, 1, 0, 0);
	cube->AddComponent(new RenderComponent(dataContainer->GetMesh("CUBE")));
	cube->GetComponent<RenderComponent>()->SetLightEnabled(true);
	//

	// Skyplane
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->GetComponent<TransformComponent>()->SetPosition(0, 100, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	//

	// Terrain
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->GetComponent<TransformComponent>()->SetScale(500, 20, 500);
	ground->AddComponent(new RenderComponent(dataContainer->GetMesh("TERRAIN")));
	//

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->GetComponent<TransformComponent>()->SetPosition(0, 5, 10);
	player->AddComponent(new PlayerScript);
	player->AddChild(m_CameraGO);
}