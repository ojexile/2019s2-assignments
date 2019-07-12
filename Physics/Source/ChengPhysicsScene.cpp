#include "ChengPhysicsScene.h"
#include "PhysicsPlayerScript.h"
#include "AudioManager.h"
ChengPhysicsScene::ChengPhysicsScene()
{
}

ChengPhysicsScene::~ChengPhysicsScene()
{
}
void ChengPhysicsScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	// Set up camera
	m_CameraGO->TRANSFORM->SetPosition(0, 0, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);

	// Ground
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->TRANSFORM->SetRotation(-90, 1, 0, 0);
	ground->AddComponent(new RenderComponent(dataContainer->GetMesh("ground")));
	ground->RENDER->SetLightEnabled(true);
	ground->SetActive(true);
	//
	float size = 50;
	// Wall
	//GameObject* wall = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	//wall->TRANSFORM->SetPosition(0, 0, -size);
	//wall->TRANSFORM->SetScale(5, 20, size * 2);
	////--------------------------------------------------------------------------------
	//GameObject* wall2 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	//wall2->TRANSFORM->SetPosition(0, 0, size);
	//wall2->TRANSFORM->SetScale(5, 20, size * 2);
	////--------------------------------------------------------------------------------
	//GameObject* wall3 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	//wall3->TRANSFORM->SetPosition(-size, 0, 0);
	//wall3->TRANSFORM->SetRotation(0, 0, 1, 0);
	//wall3->TRANSFORM->SetScale(5, 20, size * 2);
	////--------------------------------------------------------------------------------
	//GameObject* wall4 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	//wall4->TRANSFORM->SetPosition(size, 0, 0);
	//wall4->TRANSFORM->SetRotation(0, 0, 1, 0);
	//wall4->TRANSFORM->SetScale(5, 20, size * 2);
	//--------------------------------------------------------------------------------
	GameObject* wall5 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	wall5->TRANSFORM->SetPosition(0, 0, 0);
	wall5->TRANSFORM->SetRotation(0, 0, 1, 0);
	wall5->TRANSFORM->SetScale(50, 10, size / 4);
	//--------------------------------------------------------------------------------
	//// pillar
	//GameObject* pillar = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar")->Clone());
	//pillar->TRANSFORM->SetPosition(0, 0, 30);
	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANSFORM->SetPosition(0, 15, 50);
	player->AddComponent(new PhysicsPlayerScript(dataContainer->GetGameObject("ball"), dataContainer->GetGameObject("ball2")));
	player->AddChild(m_CameraGO);
	//AudioManager::GetInstance()->PlayBGM("despacito.wav");
}