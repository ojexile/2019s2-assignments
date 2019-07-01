#include "GameObjectManager.h"
GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	std::map<std::string, std::vector<GameObject*>*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second;
		for (unsigned i = list->size() - 1; i >= 0; --i)
		{
			delete (*list)[i];
			(*list).erase((*list).begin() + i);
		}
	}
}

std::map<std::string, std::vector<GameObject*>*>* GameObjectManager::GetLayerList()
{
	return &m_map_Layers;
}

GameObject* GameObjectManager::AddGameObject(GameObject* go, std::string layer)
{
	// TODO check if object already exists

	m_map_Layers[layer]->push_back(go);
	return go;
}
GameObject* GameObjectManager::AddGameObject(std::string layer)
{
	GameObject* go = new GameObject;
	m_map_Layers[layer]->push_back(go);
	return go;
}

void GameObjectManager::ClearGameObjects()
{
	// TODO ignore static objects
	std::map<std::string, std::vector<GameObject*>*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second;
		for (unsigned i = list->size() - 1; i >= 0; --i)
		{
			delete (*list)[i];
			(*list).erase((*list).begin() + i);
		}
	}
}