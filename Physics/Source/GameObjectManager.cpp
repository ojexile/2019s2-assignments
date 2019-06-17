#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

std::vector<GameObject*>* GameObjectManager::GetGOList()
{
	return &m_vec_GOList;
}

bool GameObjectManager::AddGameObject(GameObject* go)
{
	// TODO check if object already exists

	m_vec_GOList.push_back(go);
	return true;
}