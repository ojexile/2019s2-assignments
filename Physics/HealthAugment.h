#pragma once
#include "Augment.h"
class HealthAugment : public Augment
{
public:
	HealthAugment();
	virtual ~HealthAugment();

	virtual void ActiveEffect(Component* proj, GameObject* go) override;
	virtual void PassiveEffect(GameObject* go) override;

	virtual Component* Clone() { return new HealthAugment(*this); }
};

