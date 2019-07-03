#include "ChengAssignmentScene.h"
#include "ChengPlayerScript.h"
#include "GunScript.h"

ChengAssignmentScene::ChengAssignmentScene()
{
}

ChengAssignmentScene::~ChengAssignmentScene()
{
}
void ChengAssignmentScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	// Set up camera
	m_CameraGO->TRANSFORM->SetPosition(0, 0, 0);
	m_CameraGO->TRANSFORM->SetRelativePosition(0, 5, 0);
	m_CameraGO->CAMERA->SetCameraType(CameraComponent::CAM_FIRST);
	//m_CameraGO->GetComponent<CameraComponent>()->SetCameraType(CameraComponent::CAM_ORTHO);

	// Cube
	GameObject* cube = m_GameObjectManager.AddGameObject();
	cube->TRANSFORM->SetPosition(0, 15, 0);
	cube->TRANSFORM->SetScale(1.f, 1.f, 1.f);
	cube->TRANSFORM->SetRotation(90, 1, 0, 0);
	cube->AddComponent(new RenderComponent(dataContainer->GetMesh("CUBE")));
	cube->RENDER->SetLightEnabled(true);
	//
	// Skyplane
	GameObject* SkyPlane = m_GameObjectManager.AddGameObject();
	SkyPlane->TRANSFORM->SetPosition(0, 100, 0);
	SkyPlane->AddComponent(new RenderComponent(dataContainer->GetMesh("SkyPlane")));
	//SkyPlane->RENDER->SetLightEnabled(true);
	//SkyPlane->SetActive(false);
	//

	// Terrain
	GameObject* terrain = m_GameObjectManager.AddGameObject();
	terrain->TRANSFORM->SetScale(500, 20, 500);
	terrain->AddComponent(new RenderComponent(dataContainer->GetMesh("TERRAIN")));
	terrain->RENDER->SetLightEnabled(true);
	terrain->SetActive(false);
	//
	// Ground
	GameObject* ground = m_GameObjectManager.AddGameObject();
	ground->TRANSFORM->SetScale(1, 1, 1);
	ground->TRANSFORM->SetRotation(-90, 1, 0, 0);
	ground->AddComponent(new RenderComponent(dataContainer->GetMesh("GROUND")));
	ground->RENDER->SetLightEnabled(true);
	ground->SetActive(true);
	//

	// depth
	GameObject* depth = m_GameObjectManager.AddGameObject();
	depth->TRANSFORM->SetScale(1, 1, 1);
	depth->TRANSFORM->SetPosition(20, 10, 1);
	//depth->TRANSFORM->SetRotation(-90, 1, 0, 0);
	depth->AddComponent(new RenderComponent(dataContainer->GetMesh("DEPTH")));
	//depth->RENDER->SetLightEnabled(true);
	depth->SetActive(false);
	//
		// Gun

	//Player
	GameObject* player = m_GameObjectManager.AddGameObject();
	player->TRANSFORM->SetPosition(0, 0, 50);

	GameObject* gun = m_GameObjectManager.AddGameObject("UI");
	gun->TRANSFORM->SetPosition(1900, 80, 0);
	gun->AddComponent(new RenderComponent(dataContainer->GetMesh("Gun")));
	gun->RENDER->SetBillboard(false);
	gun->RENDER->SetLightEnabled(false);
	gun->AddComponent(new GunScript("Bullet", player));

	player->AddComponent(new ChengPlayerScript(gun));
	player->AddChild(m_CameraGO);
}