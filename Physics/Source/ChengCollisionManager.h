#pragma once
#include "GameObjectManager.h"
#include "GameObject.h"
class ChengCollisionManager
{
private:
	bool CheckCollision(GameObject* go1, GameObject* go2, bool rotateWall = false);
	void CollisionResponse(GameObject* go1, GameObject* go2, bool rotateWall = false);
public:
	ChengCollisionManager();
	~ChengCollisionManager();

	void Update(GameObjectManager* GOM);
};
