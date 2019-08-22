#pragma once
#include "EntityScript.h"

/*
author: lorenzo yanga
desc: entity script (not a child class anymore though) for foilage.
*/
class DestructibleEntityScript : public EntityScript
{
private:
	std::string m_sMessage;
	int m_iHealth;

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
	void SetHealth(int i);
	int GetHealth();
	void Damage(int damage);
};