#pragma once
#include "Augment.h"

class ExplodeAugment : public Augment
{
public:
	ExplodeAugment();
	virtual ~ExplodeAugment();

	virtual void ActiveEffect(Component* proj, GameObject* go) override;
	virtual void  PassiveEffect(GameObject* go) override;

	virtual Component* Clone() { return new ExplodeAugment(*this); }
};

