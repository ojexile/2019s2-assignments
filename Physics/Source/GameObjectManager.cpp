#include "GameObjectManager.h"
#include "DataContainer.h"
#include "TransformComponent.h"
GameObjectManager::GameObjectManager()
{
	this->CreateLayer(DataContainer::GetInstance()->GetShader("Default"));
	this->CreateLayer(DataContainer::GetInstance()->GetShader("Default"), "Particle");
	this->CreateLayer(DataContainer::GetInstance()->GetShader("Default"), "UI");
}

GameObjectManager::~GameObjectManager()
{
	std::map<std::string, LayerData*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		//	 it->first == key
		//	 it->second == value
		delete it->second;
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
void GameObjectManager::RemoveObject(GameObject* go)
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
				(*list).erase((*list).begin() + i);
				return;
			}
		}
	}
	DEFAULT_LOG("Failed to remove go, does not exist.");
}
// Destroy--------------------------------------------------------------------------------
void GameObjectManager::DestroyQueued()
{
	for (unsigned i = 0; i < m_ToDelete.size(); ++i)
	{
		GameObject* go = m_ToDelete.at(i);
		Destroy(go);
	}
	m_ToDelete.clear();
}
void GameObjectManager::Destroy(GameObject* go)
{
	std::map<std::string, LayerData*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second->GetGOList();
		for (unsigned i = 0; i < list->size(); ++i)
		{
			GameObject* curgo = (*list)[i];
			if (curgo == go)
			{
				delete(*list)[i];
				(*list).erase((*list).begin() + i);
				return;
			}
			// Search Child
			if (SearchDestroyChild(go, curgo))
			{
				return;
			}
		}
	}
	DEFAULT_LOG("Gameobject not deleted.");
}
bool GameObjectManager::SearchDestroyChild(GameObject* go, GameObject* curgo)
{
	for (unsigned i = 0; i < curgo->m_vec_ChildList.size(); ++i)
	{
		GameObject* child = curgo->m_vec_ChildList.at(i);
		if (child == go)
		{
			curgo->m_vec_ChildList.erase(curgo->m_vec_ChildList.begin() + i);
			return true;
		}
		if (SearchDestroyChild(go, child))
			return true;
	}
	return false;
}
//Queue for destroy--------------------------------------------------------------------------------
void GameObjectManager::QueueDestroyFromComponent(ComponentBase* com)
{
	std::map<std::string, LayerData*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second->GetGOList();
		for (unsigned i = 0; i < list->size(); ++i)
		{
			GameObject* go = (*list)[i];
			for (unsigned j = 0; j < go->m_vec_ComponentList.size(); ++j)
			{
				if (go->m_vec_ComponentList[j] == com)
				{
					m_ToDelete.push_back(go);
				}
				if (QueueSearchDestroyChildFromComponent(go, com))
					return;
			}
		}
	}
}
bool GameObjectManager::QueueSearchDestroyChildFromComponent(GameObject* go, ComponentBase* com)
{
	for (unsigned k = 0; k < go->GetChildList()->size(); ++k)
	{
		GameObject* child = go->GetChildList()->at(k);
		for (unsigned l = 0; l < child->m_vec_ComponentList.size(); ++l)
		{
			if (child->m_vec_ComponentList[l] == com)
			{
				m_ToDelete.push_back(child);
				return true;
			}
		}
		if (QueueSearchDestroyChildFromComponent(child, com))
			return true;
	}
	return false;
}
void GameObjectManager::QueueDestroy(GameObject* go)
{
	std::map<std::string, LayerData*>::iterator it;

	for (it = m_map_Layers.begin(); it != m_map_Layers.end(); it++)
	{
		// it->first == key
		// it->second == value
		std::vector<GameObject*>* list = it->second->GetGOList();
		for (unsigned i = 0; i < list->size(); ++i)
		{
			GameObject* curgo = (*list)[i];
			if (curgo == go)
			{
				m_ToDelete.push_back(curgo);
				return;
			}
			// Search Child
			if (QueueSearchDestroyChild(go, curgo))
			{
				return;
			}
		}
	}
	DEFAULT_LOG("Gameobject not deleted.");
}
bool GameObjectManager::QueueSearchDestroyChild(GameObject* go, GameObject* curgo)
{
	for (unsigned i = 0; i < curgo->m_vec_ChildList.size(); ++i)
	{
		GameObject* child = curgo->m_vec_ChildList.at(i);
		if (child == go)
		{
			m_ToDelete.push_back(child);
			return true;
		}
		if (SearchDestroyChild(go, child))
			return true;
	}
	return false;
}
//--------------------------------------------------------------------------------
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
// Instantiation
GameObject* GameObjectManager::Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer)
{
	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			AddGameObject(go, sLayer);
			TransformComponent* Trans = go->GetComponent<TransformComponent>();
			Trans->SetPosition(pos);
			Trans->SetRotation(fAngle, (int)vRot.x, (int)vRot.y, (int)vRot.z);
			Trans->SetScale(vScal.x, vScal.y, vScal.z);
			return go;
		}
		catch (const std::exception&)
		{
			DEFAULT_LOG("Instantiate failed.");
		}
	}
	DEFAULT_LOG("Instantiate failed, GORef is null.");
	return nullptr;
}
GameObject* GameObjectManager::Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer, bool isChild)
{
	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			TransformComponent* Trans = go->GetComponent<TransformComponent>();
			Trans->SetPosition(pos);
			Trans->SetScale(vScal.x, vScal.y, vScal.z);
			if (!isChild)
				AddGameObject(go, sLayer);
			return go;
		}
		catch (const std::exception&)
		{
			DEFAULT_LOG("Instantiate failed.");
		}
	}
	DEFAULT_LOG("Instantiate failed, GORef is null.");
	return nullptr;
}
GameObject* GameObjectManager::Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer)
{
	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			TransformComponent* Trans = go->GetComponent<TransformComponent>();
			Trans->SetPosition(pos);
			AddGameObject(go, sLayer);
			return go;
		}
		catch (const std::exception&)
		{
			DEFAULT_LOG("Instantiate failed.");
		}
	}
	DEFAULT_LOG("Instantiate failed, GORef is null.");
	return nullptr;
}
GameObject* GameObjectManager::Instantiate(const GameObject* goRef, std::string sLayer)
{
	// TODO change to pooling
	if (goRef)
	{
		try
		{
			GameObject* go = goRef->Clone();
			AddGameObject(go, sLayer);
			return go;
		}
		catch (const std::exception&)
		{
			DEFAULT_LOG("Instantiate failed.");
		}
	}
	DEFAULT_LOG("Instantiate failed, GORef is null.");
	return nullptr;
}