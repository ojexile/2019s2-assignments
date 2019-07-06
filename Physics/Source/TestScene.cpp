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
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Water"), "Water");
	// Set up camera
	m_CameraGO->TRANSFORM->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);

	// Cube
	GameObject* ui = m_GameObjectManager.AddGameObject("UI");
	ui->TRANSFORM->SetPosition(0, 1000, 5);
	ui->TRANSFORM->SetScale(100.f, 100.f, 1.f);
	ui->TRANSFORM->SetRotation(90, 0, 1, 0);
	ui->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	ui->RENDER->SetLightEnabled(true);
	ui->SetActive(true);
	//

	GameObject* cube = m_GameObjectManager.AddGameObject();
	cube->GetComponent<TransformComponent>()->SetPosition(0, 10, 0);
	cube->GetComponent<TransformComponent>()->SetScale(10, 1, 10);
	cube->GetComponent<TransformComponent>()->SetRotation(45, 0, 1, 0);
	cube->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	cube->GetComponent<RenderComponent>()->SetLightEnabled(true);
	cube->GetComponent<RenderComponent>()->SetBillboard(false);

	// Skyplane
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANSFORM->SetPosition(0, 100, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	SkyPlane->RENDER->SetLightEnabled(false);
	SkyPlane->SetActive(true);
	//

	// Terrain
	GameObject* terrain = m_GameObjectManager.AddGameObject();
	terrain->TRANSFORM->SetScale(500, 20, 500);
	terrain->AddComponent(new RenderComponent(dataContainer->GetMesh("Terrain")));
	terrain->RENDER->SetLightEnabled(true);
	terrain->SetActive(true);
	//

	// water
	GameObject* water = m_GameObjectManager.AddGameObject("Water");
	water->AddComponent(new RenderComponent(dataContainer->GetMesh("Water")));
	water->RENDER->SetLightEnabled(true);
	//

	// Ground
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->TRANSFORM->SetRotation(-90, 1, 0, 0);
	ground->AddComponent(new RenderComponent(dataContainer->GetMesh("Ground")));
	ground->RENDER->SetLightEnabled(true);
	ground->SetActive(false);
	//

	// depth
	GameObject* depth = m_GameObjectManager.AddGameObject();
	depth->TRANSFORM->SetScale(1, 1, 1);
	depth->TRANSFORM->SetPosition(20, 10, 1);
	//depth->TRANSFORM->SetRotation(-90, 1, 0, 0);
	depth->AddComponent(new RenderComponent(dataContainer->GetMesh("Depth")));
	depth->RENDER->SetLightEnabled(true);
	depth->SetActive(true);
	//

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANSFORM->SetPosition(0, 15, 50);
	player->AddComponent(new PlayerScript(dataContainer->GetGameObject("Cube")));
	player->AddChild(m_CameraGO);
	//AudioManager::GetInstance()->PlayBGM("despacito.wav");

	// Cat
	GameObject* cat = m_GameObjectManager.AddGameObject();
	cat->TRANSFORM->SetPosition(0, 21, 0);
	cat->TRANSFORM->SetScale(20.f, 20.f, 20.f);
	cat->AddComponent(new RenderComponent(dataContainer->GetMesh("Cat")));
	cat->RENDER->SetLightEnabled(false);
	cat->RENDER->SetBillboard(true);
}