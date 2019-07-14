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
	this->m_Camera->InitOrtho({ 100,100,10000 });
	//

	// Ground
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->TRANSFORM->SetRotation(-90, 1, 0, 0);
	ground->AddComponent(new RenderComponent(dataContainer->GetMesh("ground")));
	ground->RENDER->SetLightEnabled(true);
	ground->SetActive(false);
	//
	float size = 100;
	float height = 200;
	float thickness = 20;
	// Wall
	GameObject* wall = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	wall->TRANSFORM->SetPosition(0, 0, -size);
	wall->TRANSFORM->SetScale(thickness, height, size * 2);
	//--------------------------------------------------------------------------------
	GameObject* wall2 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	wall2->TRANSFORM->SetPosition(0, 0, size);
	wall2->TRANSFORM->SetScale(5, height, size * 2);
	//--------------------------------------------------------------------------------
	GameObject* wall3 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	wall3->TRANSFORM->SetPosition(-size, 0, 0);
	wall3->TRANSFORM->SetRotation(0, 0, 1, 0);
	wall3->TRANSFORM->SetScale(thickness, height, size * 2);
	//--------------------------------------------------------------------------------
	GameObject* wall4 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	wall4->TRANSFORM->SetPosition(size, 0, 0);
	wall4->TRANSFORM->SetRotation(0, 0, 1, 0);
	wall4->TRANSFORM->SetScale(thickness, height, size * 2);
	//--------------------------------------------------------------------------------
	GameObject* wall5 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("square")->Clone());
	wall5->TRANSFORM->SetPosition(0, 0, 0);
	wall5->TRANSFORM->SetRotation(0, 0, 1, 0);
	wall5->TRANSFORM->SetScale(thickness, height, size / 4);
	wall5->SetActive(false);

	GameObject* floor = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("wall")->Clone());
	floor->TRANSFORM->SetPosition(0, -thickness / 2, 0);
	floor->TRANSFORM->SetRotation(90, 0, 0, 1);
	floor->TRANSFORM->SetScale(thickness, size * 2, size * 2);

	GameObject* ceil = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("ceil")->Clone());
	ceil->TRANSFORM->SetPosition(0, 1000, 0);
	ceil->TRANSFORM->SetRotation(90, 0, 0, 1);
	ceil->TRANSFORM->SetScale(thickness, size * 2, size * 2);
	ceil->SetActive(false);
	//--------------------------------------------------------------------------------
	GameObject* wall6 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("floor")->Clone());
	wall6->TRANSFORM->SetPosition(0, -thickness / 2, 0);
	wall6->TRANSFORM->SetRotation(0, 0, 1, 0);
	wall6->TRANSFORM->SetScale(size * 2, thickness, size * 2);
	wall6->SetActive(false);
	//--------------------------------------------------------------------------------
	// pillar
	GameObject* pillar = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar")->Clone());
	pillar->TRANSFORM->SetPosition(0, 20, 60);
	pillar->TRANSFORM->SetScale(30, height, 30);
	GameObject* pillar2 = m_GameObjectManager.AddGameObject(dataContainer->GetGameObject("pillar")->Clone());
	pillar2->TRANSFORM->SetPosition(0, 0, -60);
	pillar2->TRANSFORM->SetScale(30, height, 30);
	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANSFORM->SetPosition(0, 15, 50);
	player->AddComponent(new PhysicsPlayerScript(dataContainer->GetGameObject("ball"), dataContainer->GetGameObject("ball2"), dataContainer->GetGameObject("ball3")));
	player->AddChild(m_CameraGO);
	//AudioManager::GetInstance()->PlayBGM("despacito.wav");
}