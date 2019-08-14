#include "DefaultScene.h"
#include "AudioManager.h"

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
	/// Player================================================================================
	// Player--------------------------------------------------------------------------------
	GameObject* Player = m_GOM.AddGameObject(dataContainer->GetGameObject("Player"));
	Player->TRANS->SetPosition(0, 16, 0);
	Player->GetComponent<EntityScript>()->Damage(5);
	/// Create Camera================================================================================
	m_CameraGO = m_GOM.AddGameObject();
	m_CameraGO->AddComponent(new CameraScript(Player));
	m_CameraGO->AddComponent(new CameraComponent);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 600;
	this->m_Camera->InitOrtho(size);
	SetCursorEnabled(false);
	// Reticle
	m_CameraGO->AddChild(dataContainer->GetGameObject("Reticle"));
	/// WORLD================================================================================
	// Terrain================================================================================
	go = m_GOM.AddGameObject();
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainPlains")->GetPos());
	go->AddComponent(new RenderComponent(dataContainer->GetChunk("Map")->GenerateMesh()));
}