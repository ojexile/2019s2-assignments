#include "RojakAssignmentScene.h"
#include "PhysicsPlayerScript.h"
#include "AudioManager.h"
#include "GunScript.h"
#include "ChengPlayerScript.h"
RojakAssignmentScene::RojakAssignmentScene()
{
}

RojakAssignmentScene::~RojakAssignmentScene()
{
}
void RojakAssignmentScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObject* go;
	// Create Camera================================================================================
	m_CameraGO = new GameObject;
	m_CameraGO->AddComponent(new CameraComponent);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	//m_GameObjectManager.AddGameObject(CameraGO);
	// Layers================================================================================
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Water"), "Water");
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Smoke"), "Smoke");
	// Set up camera
	m_CameraGO->TRANSFORM->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	this->m_Camera->InitOrtho({ 300,300,10000 });
	// UI================================================================================
	// Crosshair
	GameObject* Crosshair = m_GameObjectManager.AddGameObject("UI");
	Crosshair->TRANSFORM->SetPosition(1920 / 2, 1080 / 2, 5);
	Crosshair->TRANSFORM->SetScale(100.f, 100.f, 1.f);
	Crosshair->AddComponent(new RenderComponent(dataContainer->GetMesh("Crosshair")));
	Crosshair->RENDER->SetLightEnabled(false);
	Crosshair->SetActive(true);
	// WORLD================================================================================
	// Skyplane--------------------------------------------------------------------------------
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANSFORM->SetPosition(0, 1000, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	//
	//Board================================================================================
	float width = 90;
	float length = 150;
	float height = 200;
	float thickness = 20;
	// Walls--------------------------------------------------------------------------------
	// top--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(0, 0, -length);
	go->TRANSFORM->SetScale(thickness, height, width * 2);
	// bot--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(0, 0, length);
	go->TRANSFORM->SetScale(thickness, height, width * 2);
	// left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(-width, 0, 0);
	go->TRANSFORM->SetRotation(0, 0, 1, 0);
	go->TRANSFORM->SetScale(thickness, height, length * 2);
	// right--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(width, 0, 0);
	go->TRANSFORM->SetRotation(0, 0, 1, 0);
	go->TRANSFORM->SetScale(thickness, height, length * 2);
	// floor--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(0, -thickness / 2, 0);
	go->TRANSFORM->SetRotation(90, 0, 0, 1);
	go->TRANSFORM->SetScale(thickness, width * 2, length * 2);
	// pillar left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar")->Clone());
	go->TRANSFORM->SetPosition(-100, 0, 0);
	go->TRANSFORM->SetScale(30, height, 30);
	// Pillar2--------------------------------------------------------------------------------

	//--------------------------------------------------------------------------------
	//Player================================================================================
	// Gun--------------------------------------------------------------------------------
	GameObject* gun = m_GameObjectManager.AddGameObject("UI");
	gun->TRANSFORM->SetPosition(1900, 80, 0);
	gun->AddComponent(new RenderComponent(dataContainer->GetMesh("Gun")));
	gun->RENDER->SetBillboard(false);
	gun->RENDER->SetLightEnabled(false);
	gun->AddComponent(new GunScript(dataContainer->GetGameObject("bullet"), m_CameraGO, 0.1f, true));
	// Player--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->TRANSFORM->SetPosition(0, 0, 50);
	go->AddComponent(new ChengPlayerScript(gun, Crosshair));
	GameObject* child = dataContainer->GetGameObject("pillar")->Clone();
	go->AddChild(child);
	child->TRANSFORM->SetScale(5, 30, 5);
	go->AddChild(m_CameraGO);
}