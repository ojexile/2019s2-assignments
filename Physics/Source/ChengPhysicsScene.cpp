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

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANSFORM->SetPosition(0, 15, 50);
	player->AddComponent(new PhysicsPlayerScript(dataContainer->GetGameObject("ball"), dataContainer->GetGameObject("ball2")));
	player->AddChild(m_CameraGO);
	//AudioManager::GetInstance()->PlayBGM("despacito.wav");
}