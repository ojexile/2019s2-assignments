#pragma once
#include "GameObjectManager.h"
#include "GameObject.h"
class ChengCollisionManager
{
private:
	bool CheckCollision(GameObject* go1, GameObject* go2);
	void CollisionResponse(GameObject* go1, GameObject* go2);
public:
	ChengCollisionManager();
	~ChengCollisionManager();

	void Update();
};
