#pragma once
#include "ScriptComponent.h"
#include <vector>
/*
author: lorenzo yanga
desc: script that destroys self when its boolean is flipped OR collide. will spawn objects is m_vGOtoSpawn and trigger DestroySelf on update.
*/

class InstantiateOnDeathScript : public ScriptComponent
{
private:

	bool m_bHasTriggered;
	std::vector<GameObject*> m_vGOtoSpawn;

public:
	InstantiateOnDeathScript();
	~InstantiateOnDeathScript();

	virtual Component* Clone() { return new InstantiateOnDeathScript(*this); }

	GameObject* AddGOToList(GameObject * go);

	void Update(double dt);
	void Collide(GameObject* go);
	void Trigger();


	
};

