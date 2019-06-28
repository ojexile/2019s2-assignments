#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::Init()
{
	DataContainer* dataContainer = DataContainer::GetInstance();
	// Set up camera
	m_CameraGO->GetComponent<TransformComponent>()->setPosition(0, 0, 0);
	// Square
	GameObject* square = m_GameObjectManager.AddGameObject(new GameObject);
	square->GetComponent<TransformComponent>()->setPosition(50, 50, 10);
	square->GetComponent<TransformComponent>()->setScale(2, 2, 1);
	square->GetComponent<TransformComponent>()->setRotation(45, 0, 1, 0);
	square->AddComponent(new RenderComponent(dataContainer->GetMesh("CUBE")));
	//
}