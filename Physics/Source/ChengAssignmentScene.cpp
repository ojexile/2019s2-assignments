#include "ChengAssignmentScene.h"
#include "ChengPlayerScript.h"
#include "GunScript.h"
#include "ParticleSpawnerScript.h"

ChengAssignmentScene::ChengAssignmentScene()
{
}

ChengAssignmentScene::~ChengAssignmentScene()
{
}
void ChengAssignmentScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	// Layers
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Water"), "Water");
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Smoke"), "Smoke");
	// Set up camera
	m_CameraGO->TRANSFORM->SetPosition(0, 0, 0);
	m_CameraGO->TRANSFORM->SetRelativePosition(0, 5, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);

	// Cube
	GameObject* cube = m_GameObjectManager.AddGameObject();
	cube->GetComponent<TransformComponent>()->SetPosition(0, 5, 0);
	cube->GetComponent<TransformComponent>()->SetScale(10, 1, 10);
	cube->GetComponent<TransformComponent>()->SetRotation(45, 0, 1, 0);
	cube->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	cube->GetComponent<RenderComponent>()->SetLightEnabled(true);
	cube->GetComponent<RenderComponent>()->SetBillboard(false);
	//
	// Cube
	GameObject* cube2 = m_GameObjectManager.AddGameObject();
	cube2->GetComponent<TransformComponent>()->SetPosition(-20, 5, 0);
	cube2->GetComponent<TransformComponent>()->SetScale(2, 2, 2);
	cube2->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	cube2->GetComponent<RenderComponent>()->SetLightEnabled(true);
	cube2->GetComponent<RenderComponent>()->SetBillboard(true);
	//
	// Crosshair
	GameObject* Crosshair = m_GameObjectManager.AddGameObject("UI");
	Crosshair->TRANSFORM->SetPosition(1920 / 2, 1080 / 2, 5);
	Crosshair->TRANSFORM->SetScale(100.f, 100.f, 1.f);
	// ui->TRANSFORM->SetRotation(90, 0, 1, 0);
	Crosshair->AddComponent(new RenderComponent(dataContainer->GetMesh("Crosshair")));
	Crosshair->RENDER->SetLightEnabled(false);
	Crosshair->SetActive(true);
	//

	// Cat
	GameObject* cat = m_GameObjectManager.AddGameObject();
	cat->TRANSFORM->SetPosition(0, 15, 0);
	cat->TRANSFORM->SetScale(20.f, 20.f, 20.f);
	cat->AddComponent(new RenderComponent(dataContainer->GetAnimation("Cat")));
	cat->RENDER->SetLightEnabled(false);
	cat->RENDER->SetBillboard(true);
	//
	// Skyplane
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANSFORM->SetPosition(0, 100, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	//SkyPlane->RENDER->SetLightEnabled(true);
	//SkyPlane->SetActive(false);
	//

	// Terrain
	GameObject* terrain = m_GameObjectManager.AddGameObject();
	terrain->TRANSFORM->SetScale(500, 20, 500);
	terrain->AddComponent(new RenderComponent(dataContainer->GetMesh("Terrain")));
	terrain->RENDER->SetLightEnabled(true);
	terrain->SetActive(true);
	//
	// Ground
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->TRANSFORM->SetScale(1, 1, 1);
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
	//depth->RENDER->SetLightEnabled(true);
	depth->SetActive(true);
	depth->RENDER->SetBillboard(true);
	//

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANSFORM->SetPosition(0, 0, 50);
	// Gun
	GameObject* gun = m_GameObjectManager.AddGameObject("UI");
	gun->TRANSFORM->SetPosition(1900, 80, 0);
	gun->AddComponent(new RenderComponent(dataContainer->GetMesh("Gun")));
	gun->RENDER->SetBillboard(false);
	gun->RENDER->SetLightEnabled(false);
	gun->AddComponent(new GunScript(dataContainer->GetGameObject("Bullet"), m_CameraGO, 0.1f, true));

	player->AddComponent(new ChengPlayerScript(gun));
	player->AddChild(m_CameraGO);

	// Spawner
	GameObject* Spawner = m_GameObjectManager.AddGameObject();
	Spawner->TRANSFORM->SetPosition(0, 50, 0);
	Spawner->AddComponent(new ParticleSpawnerScript(dataContainer->GetGameObject("Rain"), 0.0002f, { 100,100,100 }, .8f));
	Spawner->SetActive(true);
	//
	// Fountain
	GameObject* Fountain = m_GameObjectManager.AddGameObject();
	Fountain->TRANSFORM->SetPosition(39, 0, 0);
	Fountain->AddComponent(new ParticleSpawnerScript(dataContainer->GetGameObject("Droplet"), 0.02f, { 2,2,2 }, .4f));
	Fountain->SetActive(true);
	//

	// water
	GameObject* water = m_GameObjectManager.AddGameObject("Water");
	water->AddComponent(new RenderComponent(dataContainer->GetMesh("Water")));
	water->TRANSFORM->SetPosition(0, -1, 0);
	water->RENDER->SetLightEnabled(false);
	water->SetActive(true);
	//
}