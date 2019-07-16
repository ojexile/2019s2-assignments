#pragma once
#include "GameObjectManager.h"
#include "GameObject.h"
#include "ChengRigidbody.h"
class ChengCollisionManager
{
public:
	
private:
	ChengRigidbody::ePhysicsTypes CheckCollision(GameObject* go1, GameObject* go2);
	void CollisionResponse(GameObject* go1, GameObject* go2, ChengRigidbody::ePhysicsTypes e);
public:
	ChengCollisionManager();
	~ChengCollisionManager();

	void Update(GameObjectManager* GOM);
};
