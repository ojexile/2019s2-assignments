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
	m_CameraGO->GetTransform()->SetPosition(0, 0, 5);
	// Square
	 GameObject* square = m_GameObjectManager.AddGameObject(new GameObject);
	 Transform* squareTrans = square->GetTransform();
	 squareTrans->SetPosition(10, 10, 10);
	 RenderComponent* squareRender = new RenderComponent(dataContainer->GetMesh("CUBE"));
	 square->AddComponent(squareRender);
	//
}