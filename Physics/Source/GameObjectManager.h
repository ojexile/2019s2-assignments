#pragma once

#include "GameObject.h"
#include "LayerData.h"
#include "Vector3.h"

#include <vector>
#include <string>
#include <map>
class GameObjectManager
{
private:
	std::map<std::string, LayerData*> m_map_Layers;
public:
	GameObjectManager();
	~GameObjectManager();

	std::map<std::string, LayerData*>* GetLayerList();

	GameObject* AddGameObject(GameObject* go, std::string layer = "Default");
	GameObject* AddGameObject(std::string layer = "Default");
	void RemoveObject(GameObject* go);
	void Destroy(GameObject*);
	bool SearchDestroyChild(GameObject* go, GameObject* curgo);
	void DestroySelf(ComponentBase* com);
	bool CreateLayer(unsigned shader, std::string layer = "Default");

	void ClearGameObjects();

	// Instantiation
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer = "Default");
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer = "Default", bool bIsChild = false);
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer = "Default");
	GameObject* Instantiate(const GameObject* goRef, std::string sLayer = "Default");
};
