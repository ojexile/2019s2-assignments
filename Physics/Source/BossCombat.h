#pragma once
#include "AIState.h"

class BossCombat : public AIState
{
private:
	GameObject* m_ShockWave;
public:
	BossCombat(GameObject* Shockwave);
	virtual ~BossCombat();

	virtual State* HandleState(ComponentBase* com) override;
	virtual void OnEnter(ComponentBase* com) override;
	virtual void OnExit(ComponentBase* com) override;
	virtual State* Clone() { return new BossCombat(*this); };
};
