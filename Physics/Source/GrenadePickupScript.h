#pragma once
#include "ScriptComponent.h"
class GrenadePickupScript : public ScriptComponent
{
public:
	GrenadePickupScript();
	virtual ~GrenadePickupScript();

	virtual Component* Clone() { return new GrenadePickupScript(*this); }
	virtual void Collide(GameObject*) override;

};

