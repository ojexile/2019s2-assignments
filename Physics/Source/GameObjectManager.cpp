#include "GameObjectManager.h"
#include "DataContainer.h"
GameObjectManager::GameObjectManager()
{
	this->CreateLayer(DataContainer::GetInstance()->GetShader("Default"));
	this->CreateLayer(DataContainer::GetInstance()->GetShader("Default"), "UI");
}

GameObjectManager::~GameObjectManager()
{
	std::map<std::string, LayerData*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second->GetGOList();
		for (unsigned i = 0; i < list->size(); ++i)
		{
			delete (*list)[i];
		}
		delete it->second;
		delete list;
	}
	m_map_Layers.clear();
}

std::map<std::string, LayerData*>* GameObjectManager::GetLayerList()
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
	m_map_Layers[layer]->GetGOList()->push_back(go);
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
	m_map_Layers[layer]->GetGOList()->push_back(go);
	return go;
}
void GameObjectManager::Destroy(GameObject* go)
{
	std::map<std::string, LayerData*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second->GetGOList();
		for (unsigned i = list->size() - 1; i >= 0; --i)
		{
			if ((*list)[i] == go)
			{
				delete(*list)[i];
				(*list).erase((*list).begin() + i);
				return;
			}
		}
	}
}
void GameObjectManager::DestroySelf(ComponentBase* com)
{
	std::map<std::string, LayerData*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second->GetGOList();
		for (unsigned i = list->size() - 1; i >= 0; --i)
		{
			GameObject* go = (*list)[i];
			for (unsigned j = 0; j < go->m_vec_ComponentList.size(); ++j)
			{
				if (go->m_vec_ComponentList[j] == com)
				{
					delete go;
					(*list).erase((*list).begin() + i);
					return;
				}
			}
		}
	}
}
bool GameObjectManager::CreateLayer(unsigned shader, std::string layer)
{
	if (m_map_Layers.count(layer) > 0)
	{
		DEFAULT_LOG("Layer already exists.");
		return false;
	}
	m_map_Layers[layer] = new LayerData(shader);
	return true;
}

void GameObjectManager::ClearGameObjects()
{
	// TODO ignore static objects
	std::map<std::string, LayerData*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second->GetGOList();
		for (unsigned i = list->size() - 1; i >= 0; --i)
		{
			delete (*list)[i];
			(*list).erase((*list).begin() + i);
		}
	}
}