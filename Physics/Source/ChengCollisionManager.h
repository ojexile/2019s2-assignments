#pragma once
#include "GameObjectManager.h"
#include "GameObject.h"
#include "ChengRigidbody.h"
class CollisionManager
{
public:

private:
	Rigidbody::ePhysicsTypes CheckCollision(GameObject* go1, GameObject* go2);
	void CheckCollision(GameObject* go1, std::vector<GameObject*>* GOList, int iIndex);
	void CollisionResponse(GameObject* go1, GameObject* go2, Rigidbody::ePhysicsTypes e);
public:
	CollisionManager();
	~CollisionManager();

	void Update(GameObjectManager* GOM);
};
