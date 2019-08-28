#pragma once
#include "ScriptComponent.h"
class CoinPickupScript : public ScriptComponent
{
public:
	CoinPickupScript();
	virtual ~CoinPickupScript();

	virtual Component* Clone() { return new CoinPickupScript(*this); }
	virtual void Collide(GameObject*) override;

};

