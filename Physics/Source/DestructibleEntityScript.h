#pragma once
#include "EntityScript.h"

/*
author: lorenzo yanga
desc: EntityScript child with a reference to a gameobject(particle spawner) that is created when the entity dies
*/
class DestructibleEntityScript : public EntityScript
{
private:
	GameObject* m_particleSpawnerRef;
	
public:
	DestructibleEntityScript();
	virtual ~DestructibleEntityScript();
	virtual ComponentBase* Clone() { return new DestructibleEntityScript(*this); };
	virtual void Update(double dt) override;

	DestructibleEntityScript* AttachGameObject(GameObject*);
};