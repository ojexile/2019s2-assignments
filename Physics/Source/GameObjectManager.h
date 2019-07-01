#pragma once

#include "GameObject.h"

#include <vector>
#include <map>

class GameObjectManager
{
private:
	std::map<std::string, std::vector<GameObject*>*> m_map_Layers;
	std::map<std::string, unsigned> m_map_Shaders;
public:
	GameObjectManager();
	~GameObjectManager();

	std::map<std::string, std::vector<GameObject*>*>* GetLayerList();
	GameObject* AddGameObject(GameObject* go, std::string layer = "default");
	GameObject* AddGameObject(std::string layer = "default");
	bool CreateLayer(std::string layer = "default");

	void ClearGameObjects();
};
