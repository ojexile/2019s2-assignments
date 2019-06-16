#include "GameObjectManager.h"

std::vector<GameObject*> GameObjectManager::m_GOList;

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

std::vector<GameObject*>* GameObjectManager::GetGOList()
{
	return &m_GOList;
}