#pragma once

#include "GameObject.h"
#include "LayerData.h"

#include <vector>
#include <map>

class GameObjectManager
{
private:
	std::map<std::string, LayerData*> m_map_Layers;
public:
	GameObjectManager();
	~GameObjectManager();

	std::map<std::string, LayerData*>* GetLayerList();

	GameObject* AddGameObject(GameObject* go, std::string layer = "default");
	GameObject* AddGameObject(std::string layer = "default");
	bool CreateLayer(unsigned shader, std::string layer = "default");

	void ClearGameObjects();
};
