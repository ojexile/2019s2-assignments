#include "RojakScene2.h"
#include "AudioManager.h"
#include "GunScript.h"
#include "ChengPlayerScript.h"
#include "MeshController.h"
#include "Blackhole.h"
#include "GauntletScript.h"
#include "SunBrightnessScript.h"
#include "Constrain.h"
#include "Utility.h"
#include "ParticleScript.h"
#include "ParticleSpawnerScript.h"
#include "ChargeBarScript.h"
RojakScene2::RojakScene2()
{
}

RojakScene2::~RojakScene2()
{
}
void RojakScene2::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObject* go;
	GameObject* go2;
	// Create Camera================================================================================
	m_CameraGO = new GameObject;
	m_CameraGO->AddComponent(new CameraComponent);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	//m_GameObjectManager.AddGameObject(CameraGO);
	// Layers================================================================================
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Water"), "Water");
	m_GameObjectManager.CreateLayer(dataContainer->GetShader("Smoke"), "Smoke");
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 600;
	this->m_Camera->InitOrtho({ size,size / aspect,10000 });
	// UI================================================================================
	// Crosshair
	GameObject* Crosshair = m_GameObjectManager.AddGameObject("UI");
	Crosshair->TRANS->SetPosition(1920 / 2, 1080 / 2, 5);
	Crosshair->TRANS->SetScale(100.f, 100.f, 1.f);
	Crosshair->AddComponent(new RenderComponent(dataContainer->GetMesh("Crosshair")));
	Crosshair->RENDER->SetLightEnabled(false);
	Crosshair->SetActive(true);
	//ScoreText--------------------------------------------------------------------------------
	go = dataContainer->GetGameObject("scoreboard");
	m_GameObjectManager.AddGameObject(go, "UI");
	// Gauntlet--------------------------------------------------------------------------------
	GameObject* Gaunt = dataContainer->GetGameObject("Gauntlet");
	m_GameObjectManager.AddGameObject(Gaunt, "UI");
	go2 = dataContainer->GetGameObject("Text");
	m_GameObjectManager.AddGameObject(go2, "UI");
	GauntletScript* gs = new GauntletScript(dataContainer->GetGameObject("bullet"), go2);
	Gaunt->AddComponent(gs);
	// ChargeBar--------------------------------------------------------------------------------
	// Text--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject("UI");
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Text"), "Gauntlet Charge: "));
	go->TRANS->SetPosition(50, 980, 30);
	go->RENDER->SetColor({ 0, 1, 1 });
	// Part--------------------------------------------------------------------------------
	go2 = m_GameObjectManager.AddGameObject("UI");
	go2->TRANS->SetPosition(50 + 400, 960, 0);
	go2->AddComponent(new ParticleSpawnerScript(dataContainer->GetGameObject("Particle"), 0.05f, 0, 0, "UI", -1.f));
	go2->SetActive(false);
	// Main--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject("UI");
	go->TRANS->SetPosition(50, 960, 0);
	//go->TRANS->SetScale(100, 100, 1);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	go->AddComponent(new ChargeBarScript(gs, go2));
	//Player================================================================================
	// Gun--------------------------------------------------------------------------------
	GameObject* gun = m_GameObjectManager.AddGameObject("UI");
	gun->TRANS->SetPosition(1900, 80, 0);
	gun->AddComponent(new RenderComponent(dataContainer->GetMesh("Gun")));
	gun->RENDER->SetBillboard(false);
	gun->RENDER->SetLightEnabled(false);
	gun->AddComponent(new GunScript(dataContainer->GetGameObject("bullet"), m_CameraGO, 0.1f, GunScript::CHARGE));
	// Player--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->TRANS->SetPosition(0, 0, 50);
	go->AddComponent(new ChengPlayerScript(gun, Crosshair, Gaunt));
	GameObject* child = dataContainer->GetGameObject("playerPillar");
	go->AddChild(child);
	go->AddChild(m_CameraGO);
	go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainMain"), Constrain::eConstrainTypes::FIXED));
	// WORLD================================================================================
	// Skyplane--------------------------------------------------------------------------------
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANS->SetPosition(0, 1000, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	// Sun--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->AddComponent(new SunBrightnessScript);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("sun")));
	go->RENDER->SetColor({ 1, 1, 0 });
	go->TRANS->SetScale(10);
	// Objects================================================================================
	// Trees--------------------------------------------------------------------------------
	const float width = 300;
	const float height = 100;
	// Tree 1--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("Tree"));
	go->TRANS->SetPosition(-width / 2, 0, -100);
	go->TRANS->SetScale(15, height, 15);
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("LeafSpawner"));
	go->TRANS->SetPosition(-width / 2, height, 0);
	go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainMain"), Constrain::eConstrainTypes::FIXED));
	// Tree 2--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("Tree"));
	go->TRANS->SetPosition(width / 2, 0, -100);
	go->TRANS->SetScale(15, height, 15);
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("LeafSpawner"));
	go->TRANS->SetPosition(width / 2, height, 0);
	// Terrain================================================================================
	// Grass--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainMain")->GetMesh()));
	// Water--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject("Water");
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("WaterPlane")));
}