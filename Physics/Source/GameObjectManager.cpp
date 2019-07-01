#include "GameObjectManager.h"
GameObjectManager::GameObjectManager()
{
	this->CreateLayer();
}

GameObjectManager::~GameObjectManager()
{
	std::map<std::string, std::vector<GameObject*>*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*> list = *it->second;
		for (auto p : list)
		{
			delete p;
		}
		list.clear();
	}
}

std::map<std::string, std::vector<GameObject*>*>* GameObjectManager::GetLayerList()
{
	return &m_map_Layers;
}

GameObject* GameObjectManager::AddGameObject(GameObject* go, std::string layer)
{
	// TODO check if object already exists
	if (m_map_Layers.count(layer) <= 0)
	{
		DEFAULT_LOG("Layer doesn't exists.");
		return nullptr;
	}
	m_map_Layers[layer]->push_back(go);
	return go;
}
GameObject* GameObjectManager::AddGameObject(std::string layer)
{
	if (m_map_Layers.count(layer) <= 0)
	{
		DEFAULT_LOG("Layer doesn't exists.");
		return nullptr;
	}
	GameObject* go = new GameObject;
	m_map_Layers[layer]->push_back(go);
	return go;
}
bool GameObjectManager::CreateLayer(std::string layer)
{
	if (m_map_Layers.count(layer) > 0)
	{
		DEFAULT_LOG("Layer already exists.");
		return false;
	}
	m_map_Layers[layer] = new std::vector<GameObject*>;
	return true;
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