#pragma once
#include "Augment.h"
class ReloadingAugment : public Augment
{
public:
	ReloadingAugment();
	virtual ~ReloadingAugment();

	virtual void ActiveEffect(Component* proj, GameObject* go) override;
	virtual void PassiveEffect(GameObject* go) override;

	virtual Component* Clone() { return new ReloadingAugment(*this); }

};

