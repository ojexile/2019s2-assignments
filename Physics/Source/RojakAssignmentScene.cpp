#include "RojakAssignmentScene.h"
#include "PhysicsPlayerScript.h"
#include "AudioManager.h"
#include "GunScript.h"
#include "ChengPlayerScript.h"
#include "MeshController.h"
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
	// Gauntlet
	GameObject* Gaunt = m_GameObjectManager.AddGameObject("UI");
	Gaunt->TRANSFORM->SetPosition(250, 1080 - 800, 5);
	Gaunt->TRANSFORM->SetScale(800.f, 800.f, 1.f);
	Gaunt->AddComponent(new RenderComponent(dataContainer->GetMesh("Gaunt")));
	Gaunt->RENDER->SetLightEnabled(false);
	MeshController<Mesh>* meshController = new MeshController<Mesh>;
	meshController->AddMesh("gaunt", dataContainer->GetMesh("Gaunt"));
	meshController->AddMesh("notGaunt", dataContainer->GetMesh("Crosshair"));
	Gaunt->AddComponent(meshController);
	Gaunt->SetActive(false);
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
	go->AddComponent(new ChengPlayerScript(gun, Crosshair, Gaunt));
	GameObject* child = dataContainer->GetGameObject("pillar")->Clone();
	go->AddChild(child);
	child->TRANSFORM->SetScale(5, 30, 5);
	go->AddChild(m_CameraGO);
	// WORLD================================================================================
	// Skyplane--------------------------------------------------------------------------------
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANSFORM->SetPosition(0, 1000, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	//
	//Board================================================================================
	float width = 120;
	float length = 120;
	float height = 120;
	float holeWidth = 20;
	float thickness = 20;
	float fOffset = -thickness;
	// Walls--------------------------------------------------------------------------------
	// top--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(0, 0, -length);
	go->TRANSFORM->SetScale(thickness, height, width * 2 + fOffset);
	// bot left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(-(width / 2 + holeWidth / 2), 0, length);
	go->TRANSFORM->SetScale(thickness, height, width - holeWidth / 2);
	// bot right--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition((width / 2 + holeWidth / 2), 0, length);
	go->TRANSFORM->SetScale(thickness, height, width - holeWidth / 2);
	// goal--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("goal")->Clone());
	go->TRANSFORM->SetPosition(0, 0, length + 20);
	go->TRANSFORM->SetScale(thickness, height, holeWidth + 40);
	// left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(-width, 0, 0);
	go->TRANSFORM->SetRotation(0, 0, 1, 0);
	go->TRANSFORM->SetScale(thickness, height, length * 2 + fOffset);
	// right--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(width, 0, 0);
	go->TRANSFORM->SetRotation(0, 0, 1, 0);
	go->TRANSFORM->SetScale(thickness, height, length * 2 + fOffset);
	// floor--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	go->TRANSFORM->SetPosition(0, -thickness / 2, 0);
	go->TRANSFORM->SetRotation(90, 0, 0, 1);
	go->TRANSFORM->SetScale(thickness, width * 2, length * 2);
	// pillar left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar")->Clone());
	go->TRANSFORM->SetPosition(-80, 0, 0);
	go->TRANSFORM->SetScale(25, height, 25);
	// Pillar right--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar")->Clone());
	go->TRANSFORM->SetPosition(80, 0, 0);
	go->TRANSFORM->SetScale(25, height, 25);
}