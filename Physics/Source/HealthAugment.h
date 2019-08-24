#pragma once
#include "Augment.h"
class HealthAugment : public Augment
{
public:
	HealthAugment();
	virtual ~HealthAugment();

	virtual void ActiveEffect(Component* proj, GameObject* go) override;
	virtual void PassiveEffect() override;
	virtual void RemovePassive() override;

	virtual Component* Clone() { return new HealthAugment(*this); }
};

