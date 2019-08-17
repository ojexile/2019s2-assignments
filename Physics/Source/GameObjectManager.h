#pragma once
#include "GameObject.h"
#include "LayerData.h"
#include "Vector3.h"
#include "ComponentBase.h"

#include <vector>
#include <string>
#include <map>
class GameObjectManager
{
private:
	std::map<std::string, LayerData*> m_map_Layers;
	std::vector<GameObject*> m_ToDelete;

	void Destroy(GameObject*);
	bool SearchDestroyChild(GameObject* go, GameObject* curgo);
public:
	GameObjectManager();
	~GameObjectManager();

	std::map<std::string, LayerData*>* GetLayerList();

	GameObject* AddGameObject(GameObject* go, std::string layer = "Default");
	GameObject* AddGameObject(std::string layer = "Default");
	void RemoveObject(GameObject* go);
	bool CreateLayer(unsigned shader, std::string layer = "Default");
	void ClearGameObjects();

	void QueueDestroyFromComponent(ComponentBase* com);
	void QueueDestroy(GameObject*);
	bool QueueSearchDestroyChild(GameObject* go, GameObject* curgo);
	bool QueueSearchDestroyChildFromComponent(GameObject* go, ComponentBase* com);

	void DestroyQueued();
	// Instantiation
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, Vector3 vRot, float fAngle, std::string sLayer = "Default");
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, Vector3 vScal, std::string sLayer = "Default", bool bIsChild = false);
	GameObject* Instantiate(const GameObject* goRef, Vector3 pos, std::string sLayer = "Default");
	GameObject* Instantiate(const GameObject* goRef, std::string sLayer = "Default");
};
