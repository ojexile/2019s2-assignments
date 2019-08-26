#pragma once
#include "ScriptComponent.h"
class RepairPickupScript :
	public ScriptComponent
{
public:
	RepairPickupScript();
	virtual ~RepairPickupScript();

	virtual Component* Clone() { return new RepairPickupScript(*this); }
	virtual void Collide(GameObject*) override;
};

