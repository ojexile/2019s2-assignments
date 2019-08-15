#include "DefaultScene.h"
#include "AudioManager.h"
#include "ChunkCollider.h"

#include "PlayerScript.h"
#include "Utility.h"
#include "CameraScript.h"
#include "InventoryScript.h"
#include "WeaponScript.h"
#include "StaminaScript.h"
DefaultScene::DefaultScene()
{
}

DefaultScene::~DefaultScene()
{
}
void DefaultScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	GameObject* go = nullptr;
	GameObject* go2 = nullptr;
	/// Layers================================================================================
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	m_GOM.AddGameObject(dataContainer->GetGameObject("FPS"), "UI");
	// Inventory--------------------------------------------------------------------------------
	std::vector<GameObject*> InventorySlots;
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100, 100);
	InventorySlots.push_back(go);
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110, 100);
	InventorySlots.push_back(go);
	//
	go = m_GOM.AddGameObject(GetGO("InventorySlot"), "UI");
	go->TRANS->SetPosition(1920 - 100 - 110 - 110, 100);
	InventorySlots.push_back(go);
	// Stamina--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject("UI");
	go->TRANS->SetPosition(50, 50, 0);
	go->TRANS->SetScale(200, 50, 1);
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	go->RENDER->SetColor(0.7f, 0.7f, 0.7f);

	GameObject* stam = m_GOM.AddGameObject("UI");
	stam->TRANS->SetPosition(50, 50, 0);
	stam->AddComponent(new RenderComponent(dataContainer->GetMesh("Quad")));
	stam->RENDER->SetColor(1, 1, 0);

	/// Player================================================================================
	// Reticle
	go2 = dataContainer->GetGameObject("Reticle");

	//Gun------------------------------------------------------------------------------------
	GameObject* gun = dataContainer->GetGameObject("Gun");
	gun->TRANS->SetRelativePosition(1, 1, 0);
	// Player--------------------------------------------------------------------------------
	GameObject* Player = m_GOM.AddGameObject();
	Player->AddComponent(new PlayerScript(go2, gun));
	Player->AddChild(gun);
	Player->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	Player->RIGID->SetMat(0.9f, 0.f);
	Player->AddComponent(new RenderComponent(dataContainer->GetMesh("Player")));

	Player->RENDER->SetActive(true);

	Player->TRANS->SetPosition(0, 16, 0);
	Player->TRANS->SetScale(0.5, 0.5, 0.5);
	Player->AddComponent(new InventoryScript(gun, InventorySlots));
	Player->AddComponent(new StaminaScript(stam));
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraScript(Player));
	m_CameraGO->AddComponent(new CameraComponent);
	m_CameraGO->AddChild(go2);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 100;
	this->m_Camera->InitOrtho(size);
	SetCursorEnabled(false);

	go = m_GOM.AddGameObject(dataContainer->GetGameObject("BaseEnemy"));
	go->TRANS->SetPosition(6, 18.5, 5);


	go = m_GOM.AddGameObject(dataContainer->GetGameObject("BaseEnemy"));
	go->TRANS->SetPosition(-6, 18.5, 25);

	go = dataContainer->GetGameObject("Muzzle");
	go->TRANS->SetScale(3);

	gun->AddChild(go);
	gun->GUN->AddPart(go);

	go = dataContainer->GetGameObject("Stock");
	go->TRANS->SetScale(3);

	gun->AddChild(go);
	gun->GUN->AddPart(go);
	/// WORLD================================================================================
	// Terrain================================================================================
	go = m_GOM.AddGameObject();
	go->AddComponent(new RenderComponent(dataContainer->GetChunk("Map")->GenerateMeshBiomed()));
	go->AddComponent(new BiomeComponent(BiomeComponent::BIOME_SNOW));
	go->AddComponent(new ChunkCollider(dataContainer->GetChunk("Map")));

	go = m_GOM.AddGameObject();
	go->TRANS->SetPosition(Vector3(16, 0, 0));
	go->AddComponent(new RenderComponent(dataContainer->GetChunk("goldmine")->GenerateMeshBiomed()));
	go->AddComponent(new BiomeComponent(BiomeComponent::BIOME_PLAINS));
	go->AddComponent(new ChunkCollider(dataContainer->GetChunk("goldmine")));
	// Parts
	go = m_GOM.AddGameObject(GetGO("Muzzle"));
	go->TRANS->SetPosition(5, 16, 5);
}