 #include "DefaultScene.h"
#include "AudioManager.h"
#include "ChunkCollider.h"

#include "PlayerScript.h"
#include "WeaponScript.h"
#include "Utility.h"
#include "CameraScript.h"
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

	// Player--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject();
	go->TRANS->SetScale(.5, 0.5, .5);
	go->TRANS->SetPosition(2, 17.5, 2);
	go->AddComponent(new PlayerScript());
	go->AddComponent(new Rigidbody(Rigidbody::BALL, true));
	go->RIGID->SetMat(0.9f, 0.f);
	go->AddComponent(new WeaponScript(dataContainer->GetGameObject("Bullet")));
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraScript(go));
	m_CameraGO->AddComponent(new CameraComponent);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 600;
	this->m_Camera->InitOrtho(size);
	/// WORLD================================================================================
	// Skyplane--------------------------------------------------------------------------------
	GameObject* SkyPlane = m_GOM.AddGameObject();
	SkyPlane->TRANS->SetPosition(0, 340, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	SkyPlane->RENDER->SetLightEnabled(true);
	/// Plains================================================================================
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
	go->AddComponent(new RenderComponent(dataContainer->GetChunk("Map")->GenerateMesh()));
	go->AddComponent(new ChunkCollider(dataContainer->GetChunk("Map")));
}