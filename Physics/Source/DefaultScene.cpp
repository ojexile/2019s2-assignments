 #include "DefaultScene.h"
#include "AudioManager.h"

#include "PlayerScript.h"
#include "WeaponScript.h"
#include "Utility.h"

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
	/// Create Camera================================================================================
	m_CameraGO = new GameObject;
	m_CameraGO->AddComponent(new CameraComponent);
	m_Camera = m_CameraGO->GetComponent<CameraComponent>()->GetCamera();
	/// Layers================================================================================
	// Set up camera
	m_CameraGO->TRANS->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	Vector3 WindowSize = StringToVector(Preferences::GetPref(Resources::PreferencesTerm::WindowSize));
	float aspect = WindowSize.x / WindowSize.y;
	float size = 600;
	this->m_Camera->InitOrtho(size);
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	m_GOM.AddGameObject(dataContainer->GetGameObject("FPS"), "UI");

	// Player--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject();
	go->TRANS->SetScale(1);
	go->AddChild(m_CameraGO);
	go->AddComponent(new PlayerScript());
	go->AddComponent(new Rigidbody(Rigidbody::BALL));
	go->RIGID->SetMat(0.9f, 0.f);
	go->AddComponent(new WeaponScript(dataContainer->GetGameObject("Bullet")));
	go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::LIMIT));
	go->AddComponent(new RenderComponent(dataContainer->GetMesh("Cube")));
	/// WORLD================================================================================
	// Skyplane--------------------------------------------------------------------------------
	GameObject* SkyPlane = m_GOM.AddGameObject();
	SkyPlane->TRANS->SetPosition(0, 340, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	SkyPlane->RENDER->SetLightEnabled(true);
	/// Plains================================================================================
	// Terrain================================================================================
	go = m_GOM.AddGameObject();
	go->TRANS->SetPosition(dataContainer->GetHeightMap("TerrainPlains")->GetPos());
	go->AddComponent(new RenderComponent(dataContainer->GetHeightMap("TerrainPlains")->GetMesh()));
}