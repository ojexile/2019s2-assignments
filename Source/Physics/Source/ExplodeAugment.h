#pragma once
#include "Augment.h"

class ExplodeAugment : public Augment
{
public:
	ExplodeAugment();
	virtual ~ExplodeAugment();

	virtual void ActiveEffect(Component* proj, GameObject* go) override;
	virtual void PassiveEffect() override;
	virtual void RemovePassive() override;

	virtual Augment* Clone() { return new ExplodeAugment(*this); }
};

