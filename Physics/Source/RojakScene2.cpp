#include "RojakScene2.h"
#include "AudioManager.h"

#include "ChengPlayerScript.h"
#include "MeshController.h"
#include "Blackhole.h"

#include "SunBrightnessScript.h"
#include "Constrain.h"
#include "Utility.h"

#include "WorldValues.h"

#include "ChengRigidbody.h"

RojakScene2::RojakScene2()
{
}

RojakScene2::~RojakScene2()
{
}
void RojakScene2::Init()
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
	this->m_Camera->InitOrtho({ size, 0,10000 });
	/// UI================================================================================
	// FPS--------------------------------------------------------------------------------
	m_GOM.AddGameObject(dataContainer->GetGameObject("FPS"), "UI");
	// Player--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject();
	GameObject* player = go;
	go->AddChild(m_CameraGO);
	go->AddComponent(new PlayerScript());
	go->AddComponent(new ChengRigidbody(ChengRigidbody::BALL));
	go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::LIMIT));
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
	/// Trees--------------------------------------------------------------------------------
	// tree 1--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("Tree"));
	go->TRANS->SetPosition(100, 0, 100);
	go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::FIXED));
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("LeafSpawner"));
	go->TRANS->SetPosition(100, 100, 100);
	go->SetActive(false);
	// tree 2--------------------------------------------------------------------------------
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("Tree"));
	go->TRANS->SetPosition(150, 0, 100);
	go->AddComponent(new Constrain(dataContainer->GetHeightMap("TerrainPlains"), Constrain::eConstrainTypes::FIXED));
	go = m_GOM.AddGameObject(dataContainer->GetGameObject("LeafSpawner"));
	go->TRANS->SetPosition(150, 100, 100);
	go->SetActive(false);
}