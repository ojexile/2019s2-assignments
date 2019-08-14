#include "DefaultScene.h"
#include "AudioManager.h"

#include "PlayerScript.h"
#include "Utility.h"
#include "CameraScript.h"
#include "WeaponScript.h"

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
	/// Player================================================================================
	// Reticle
	go2 =dataContainer->GetGameObject("Reticle");
	
	//Gun------------------------------------------------------------------------------------
	GameObject* gun = m_GOM.AddGameObject(dataContainer->GetGameObject("Gun"));
	gun->TRANS->SetPosition(5, 16, 5);
	// Player--------------------------------------------------------------------------------
	GameObject* Player = m_GOM.AddGameObject();
	Player->AddComponent(new PlayerScript(go2, gun));
	Player->AddComponent(new Rigidbody(Rigidbody::BALL, false));
	Player->RIGID->SetMat(0.9f, 0.f);
	Player->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::LIMIT));
	Player->AddComponent(new RenderComponent(dataContainer->GetMesh("Player")));
	
	Player->RENDER->SetActive(false);
	
	Player->TRANS->SetPosition(0, 16, 0);
	Player->GetComponent<EntityScript>()->Damage(5);
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
	float size = 600;
	this->m_Camera->InitOrtho(size);
	SetCursorEnabled(false);

	go = m_GOM.AddGameObject(dataContainer->GetGameObject("BaseEnemy"));
	go->TRANS->SetPosition(6, 16.5, 5);

	go = dataContainer->GetGameObject("Muzzle");
	go->TRANS->SetScale(3);

	gun->AddChild(go);
	gun->GUN->AddPart(go);

	/// WORLD================================================================================
	// Terrain================================================================================
	go = m_GOM.AddGameObject();
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainPlains")->GetPos());
	go->AddComponent(new RenderComponent(dataContainer->GetChunk("Map")->GenerateMesh()));
}