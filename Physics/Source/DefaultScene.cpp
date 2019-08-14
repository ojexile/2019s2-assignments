#include "DefaultScene.h"
#include "AudioManager.h"
#include "ChunkCollider.h"

#include "PlayerScript.h"
#include "Utility.h"
#include "CameraScript.h"
#include "InventoryScript.h"

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
	/// Player================================================================================
	// Reticle
	go2 =dataContainer->GetGameObject("Reticle");
	// Player--------------------------------------------------------------------------------
	GameObject* Player = m_GOM.AddGameObject();
	GameObject* gun = dataContainer->GetGameObject("Gun");
	Player->AddComponent(new PlayerScript(go2, gun));
	Player->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	Player->RIGID->SetMat(0.9f, 0.f);
	//Player->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::LIMIT));
	Player->AddComponent(new RenderComponent(dataContainer->GetMesh("Player")));
	Player->TRANS->SetPosition(0, 16, 0);
	Player->TRANS->SetScale(0.5, 0.5, 0.5);
	Player->AddComponent(new InventoryScript(gun, InventorySlots));
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
	/// WORLD================================================================================
	// Terrain================================================================================
	go = m_GOM.AddGameObject();
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainPlains")->GetPos() - Vector3(200,0,0));
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainPlains")->GetMeshBiomed()));
	go->AddComponent(new BiomeComponent(BiomeComponent::BIOME_PLAINS));
	//go->GetComponent<BiomeComponent>(true)->SetMeshBiomedPointer(dynamic_cast<MeshBiomed*>(dataContainer->GetHeightMap("TerrainPlains")->GetMesh()));
	
	
	/*go = m_GOM.AddGameObject();
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainTest")->GetPos());
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainTest")->GetMesh()));
	go->AddComponent(new BiomeComponent(BiomeComponent::BIOME_PLAINS));
	*/
	
	//go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainPlains")->GetPos());
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