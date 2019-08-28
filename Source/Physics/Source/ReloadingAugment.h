#pragma once
#include "Augment.h"
class ReloadingAugment : public Augment
{
public:
	ReloadingAugment();
	virtual ~ReloadingAugment();

	virtual void ActiveEffect(Component* proj, GameObject* go) override;
	virtual void PassiveEffect() override;
	virtual void RemovePassive() override;

	virtual Augment* Clone() { return new ReloadingAugment(*this); }

private:
	float m_fMultiplier;

};

