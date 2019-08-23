#pragma once
#include "Augment.h"
class BlackHoleAugment : public Augment
{
public:
	BlackHoleAugment();
	virtual ~BlackHoleAugment();

	virtual void ActiveEffect(Component* proj, GameObject* go) override;
	virtual void PassiveEffect() override;
	virtual void RemovePassive() override;

	virtual Component* Clone() { return new BlackHoleAugment(*this); }
};

