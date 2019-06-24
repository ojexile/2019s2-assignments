#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	for (int i = (int)m_vec_GOList.size() - 1; i >= 0; --i)
	{
		delete m_vec_GOList[i];
		m_vec_GOList.erase(m_vec_GOList.begin() + i);
	}
}

std::vector<GameObject*>* GameObjectManager::GetGOList()
{
	return &m_vec_GOList;
}

GameObject* GameObjectManager::AddGameObject(GameObject* go)
{
	// TODO check if object already exists

	m_vec_GOList.push_back(go);
	return go;
}

void GameObjectManager::ClearGameObjects()
{
	// TODO ignore static objects
	for (unsigned i = m_vec_GOList.size() - 1; i >= 0; --i)
	{
		delete m_vec_GOList[i];
		m_vec_GOList.erase(m_vec_GOList.begin() + i);
	}
}