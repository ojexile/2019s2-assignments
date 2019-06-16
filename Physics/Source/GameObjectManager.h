#pragma once

#include "GameObject.h"

#include <vector>

class GameObjectManager
{
private:
	static std::vector<GameObject*> m_GOList;
public:
	GameObjectManager();
	~GameObjectManager();

	static std::vector<GameObject*>* GetGOList();
};
