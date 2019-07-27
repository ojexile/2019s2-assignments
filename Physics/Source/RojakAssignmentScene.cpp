#include "RojakAssignmentScene.h"
#include "AudioManager.h"
#include "GunScript.h"
#include "ChengPlayerScript.h"
#include "MeshController.h"
#include "Blackhole.h"
#include "GauntletScript.h"
#include "SunBrightnessScript.h"
#include "Constrain.h"
#include "Utility.h"
#include "Preferences.h"
#include "ChargeBarScript.h"
#include "ParticleSpawnerScript.h"
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
	GameObject* Gaunt = m_GameObjectManager.AddGameObject("UI");
	Gaunt->TRANS->SetPosition(250, 1080 - 800, 5);
	Gaunt->TRANS->SetScale(800.f, 800.f, 1.f);
	Gaunt->AddComponent(new RenderComponent(dataContainer->GetMesh("Gaunt")));
	Gaunt->RENDER->SetLightEnabled(false);
	MeshController<Mesh>* meshController = new MeshController<Mesh>;
	meshController->AddMesh("Gaunt", dataContainer->GetMesh("Gaunt"));
	meshController->AddMesh("GauntSoul", dataContainer->GetMesh("GauntSoul"));
	meshController->AddMesh("GauntReality", dataContainer->GetMesh("GauntReality"));
	meshController->AddMesh("GauntSpace", dataContainer->GetMesh("GauntSpace"));
	meshController->AddMesh("GauntPower", dataContainer->GetMesh("GauntPower"));
	meshController->AddMesh("GauntTime", dataContainer->GetMesh("GauntTime"));
	meshController->AddMesh("GauntMind", dataContainer->GetMesh("GauntMind"));
	meshController->AddMesh("GauntFist", dataContainer->GetMesh("GauntFist"));
	meshController->AddMesh("GauntSnap", dataContainer->GetMesh("GauntSnap"));
	Gaunt->AddComponent(meshController);
	GauntletScript* gs = new GauntletScript(dataContainer->GetGameObject("bullet"));
	Gaunt->AddComponent(gs);
	Gaunt->SetActive(true);
	// ChargeBar--------------------------------------------------------------------------------
	// Text
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
	////Repel--------------------------------------------------------------------------------
	//GameObject* repel = new GameObject;
	//repel->AddComponent(new Blackhole(-20000, 700));
	//repel->SetActive(false);
	// Player--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->TRANS->SetPosition(0, 0, 50);
	go->AddComponent(new ChengPlayerScript(gun, Crosshair, Gaunt));
	GameObject* child = dataContainer->GetGameObject("playerPillar");
	go->AddChild(child);
	go->AddChild(m_CameraGO);
	//go->AddComponent(new Constrain(dataContainer->GetHeightMap("Terrain"), Constrain::eConstrainTypes::LIMIT));
	// WORLD================================================================================
	// Skyplane--------------------------------------------------------------------------------
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANS->SetPosition(0, 2000, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	// Sun--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->AddComponent(new SunBrightnessScript);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("ball")));
	go->RENDER->SetColor({ 1, 1, 0 });
	go->TRANS->SetScale(10);
	// Rain--------------------------------------------------------------------------------
	go = dataContainer->GetGameObject("RainSpawner");
	m_GameObjectManager.AddGameObject(go);
	//Board================================================================================
	float width = 80;
	float length = 120;
	float height = 70;
	float holeWidth = 40;
	float thickness = 20;
	float fOffset = -thickness;
	// Walls--------------------------------------------------------------------------------
	// mid--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("square"));
	go->TRANS->SetPosition(0, 0, -length / 2);
	go->TRANS->SetRotation(45, 0, 1, 0);
	go->TRANS->SetScale(thickness, height, thickness);
	// top--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall"));
	go->TRANS->SetPosition(0, 0, -length);
	go->TRANS->SetScale(thickness, height, width * 2 + fOffset);
	// bot left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall"));
	go->TRANS->SetPosition(-(width / 2 + holeWidth / 2), 0, length - 20);
	go->TRANS->SetRotation(60, 0, 1, 0);
	go->TRANS->SetRotation(60, 0, 1, 0);
	go->TRANS->SetScale(thickness, height, width - holeWidth / 2);
	// bot right--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall"));
	go->TRANS->SetPosition((width / 2 + holeWidth / 2), 0, length - 20);
	go->TRANS->SetRotation(-60, 0, 1, 0);
	go->TRANS->SetScale(thickness, height, width - holeWidth / 2);
	// goal--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("goal"));
	go->TRANS->SetPosition(0, 0, length + 20);
	go->TRANS->SetScale(thickness, height, holeWidth + 40);
	//go->AddComponent(new Blackhole(1000, 200));
	// left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall"));
	go->TRANS->SetPosition(-width, 0, 0);
	go->TRANS->SetRotation(0, 0, 1, 0);
	go->TRANS->SetScale(thickness, height, length * 2 + fOffset);
	// right--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall"));
	go->TRANS->SetPosition(width, 0, 0);
	go->TRANS->SetRotation(0, 0, 1, 0);
	go->TRANS->SetScale(thickness, height, length * 2 + fOffset);
	// floor--------------------------------------------------------------------------------
	//go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall"));
	//go->TRANS->SetPosition(0, -thickness / 2, 0);
	//go->TRANS->SetRotation(90, 0, 0, 1);
	//go->TRANS->SetScale(thickness, 1000, 1000);
	// pillar left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar"));
	go->TRANS->SetPosition(-width / 2, 0, 0);
	go->TRANS->SetScale(15, height, 15);
	// Pillar right--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar"));
	go->TRANS->SetPosition(width / 2, 0, 0);
	go->TRANS->SetScale(15, height, 15);
	// Pillar Bot Right--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar"));
	go->TRANS->SetPosition(width / 2 + 25, 0, 80);
	go->TRANS->SetScale(5, height, 5);
	// Pillar Bot Left--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar"));
	go->TRANS->SetPosition(-width / 2 - 25, 0, 80);
	go->TRANS->SetScale(5, height, 5);
	//Paddle
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("paddle"));
	go->RENDER->SetColor({ 0,0,1 });
	go->TRANS->SetPosition(-holeWidth, 0, length - 17.5f);
	go->TRANS->SetRotation(-90, 0, 1, 0);
	//Paddle
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("paddleRight"));
	go->RENDER->SetColor({ 0,0,1 });
	go->TRANS->SetPosition(holeWidth, 0, length - 17.5f);
	go->TRANS->SetRotation(90, 0, 1, 0);
	// Obstacles--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("fanBlade"));
	go->TRANS->SetPosition(0, 0, -length / 8);
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("fanBlade"));
	go->TRANS->SetPosition(0, 0, -length / 8);
	go->TRANS->SetRotation(120, 0, 1, 0);
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("fanBlade"));
	go->TRANS->SetPosition(0, 0, -length / 8);
	go->TRANS->SetRotation(240, 0, 1, 0);
	// Hole
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillarHole"));
	go->TRANS->SetPosition(width / 2, 0, -length / 2);
	go->RENDER->SetColor({ 0,0,0 });
	// Hole
	go = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("squareHole"));
	go->TRANS->SetPosition(-width / 2, 0, -length / 2);
	go->RENDER->SetColor({ 0,0,0 });
	// Terrain--------------------------------------------------------------------------------
	go = m_GameObjectManager.AddGameObject();
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("Terrain")->GetMesh()));
	go->SetActive(true);
}