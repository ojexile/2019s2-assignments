#pragma once
#include "EntityScript.h"

/*
author: lorenzo yanga
desc: EntityScript child with a reference that is created when the entity dies.
		to be used with destructible foilage/interactable objects
*/
class DestructibleEntityScript : public EntityScript
{
private:
	std::string m_sMessage;

public:
	DestructibleEntityScript();
	DestructibleEntityScript(std::string s);
	virtual ~DestructibleEntityScript();
	virtual Component* Clone() {
		return new DestructibleEntityScript(*this);
	};
	virtual void Update(double dt) override;
	virtual void Collide(GameObject* );
	void SetMessage(std::string s);
	
};