#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::Init()
{
	// Set up camera
	m_CameraGO->GetTransform()->SetPosition(0, 0, 5);
	// Square
	GameObject* square = new GameObject;
	m_GameObjectManager.AddGameObject(square);
	//
}