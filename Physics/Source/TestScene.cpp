#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::InitCamera()
{
	GameObject* CameraGO = new GameObject;
	CameraGO->AddComponent(new CameraComponent);
	m_CameraGO = CameraGO;
	m_Camera = CameraGO->GetComponent<CameraComponent>()->GetCamera();
	Transform& trans = *CameraGO->GetComponent<Transform>();
	trans.SetPosition({ 0, 0, 5 });
	m_GameObjectManager.AddGameObject(CameraGO);
}
void TestScene::Init()
{
	InitCamera();
	// Square
	GameObject* square = new GameObject;
	m_GameObjectManager.AddGameObject(square);
	//
}