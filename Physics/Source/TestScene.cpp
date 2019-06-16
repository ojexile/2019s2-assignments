#include "TestScene.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
void TestScene::Init()
{
	std::vector<GameObject*>* GOList = GameObjectManager::GetGOList();
	// Square
	GameObject* square = new GameObject;
	square->m_vPosition = { 10,10,0 };
	GOList->push_back(square);
	//
}