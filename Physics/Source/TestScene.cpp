#include "TestScene.h"
#include "PlayerScript.h"
#include "AudioManager.h"
TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	// Layers
	// m_GameObjectManager.CreateLayer(dataContainer->GetShader("water"), "second");
	// Set up camera
	m_CameraGO->TRANSFORM->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);

	// Cube
	GameObject* cube = m_GameObjectManager.AddGameObject("UI");
	cube->TRANSFORM->SetPosition(0, 1000, 5);
	cube->TRANSFORM->SetScale(100.f, 100.f, 1.f);
	cube->TRANSFORM->SetRotation(90, 0, 1, 0);
	cube->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	cube->RENDER->SetLightEnabled(true);
	cube->SetActive(true);

	//
	// Skyplane
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANSFORM->SetPosition(0, 100, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	SkyPlane->RENDER->SetLightEnabled(false);
	SkyPlane->SetActive(false);
	//

	// Terrain
	GameObject* terrain = m_GameObjectManager.AddGameObject();
	terrain->TRANSFORM->SetScale(500, 20, 500);
	terrain->AddComponent(new RenderComponent(dataContainer->GetMesh("TERRAIN")));
	terrain->RENDER->SetLightEnabled(true);
	terrain->SetActive(false);
	//

	// Ground
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->TRANSFORM->SetScale(1, 1, 1);
	ground->TRANSFORM->SetRotation(-90, 1, 0, 0);
	ground->AddComponent(new RenderComponent(dataContainer->GetMesh("GROUND")));
	ground->RENDER->SetLightEnabled(true);
	//

	// depth
	GameObject* depth = m_GameObjectManager.AddGameObject();
	depth->TRANSFORM->SetScale(1, 1, 1);
	depth->TRANSFORM->SetPosition(20, 10, 1);
	//depth->TRANSFORM->SetRotation(-90, 1, 0, 0);
	depth->AddComponent(new RenderComponent(dataContainer->GetMesh("DEPTH")));
	depth->RENDER->SetLightEnabled(true);
	depth->SetActive(false);
	//

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANSFORM->SetPosition(0, 15, 50);
	player->AddComponent(new PlayerScript);
	player->AddChild(m_CameraGO);
	AudioManager::GetInstance()->PlayBGM("despacito.wav");

	// Cat
	GameObject* cat = m_GameObjectManager.AddGameObject();
	cat->TRANSFORM->SetPosition(0, 20, 0);
	cat->TRANSFORM->SetScale(50.f, 50.f, 50.f);
	cat->AddComponent(new RenderComponent(dataContainer->GetMesh("Cat")));
	cat->RENDER->SetLightEnabled(false);
	cat->RENDER->SetBillboard(true);
}