#pragma once

#include "GameObject.h"

#include <vector>

class GameObjectManager
{
private:
	std::vector<GameObject*> m_vec_GOList;
public:
	GameObjectManager();
	~GameObjectManager();

	std::vector<GameObject*>* GetGOList();
	GameObject* AddGameObject(GameObject* go);

	void ClearGameObjects();
};
