#pragma once
#include "State.h"
#include "GameObject.h"
class AIState :
	public State
{
private:
protected:
	State* m_Combat;
	//
	bool PlayerInRange(ComponentBase* com);
	bool PlayerInRange(ComponentBase* com, float dist);
	Vector3 DirToPlayer(ComponentBase* com);
	void DamagePlayer(int damage, float force, Vector3 Dir);

public:
	AIState(State* Combat);
	virtual ~AIState();

	virtual State* HandleState(ComponentBase* com) = 0;
	virtual void OnEnter(ComponentBase* com) = 0;
	virtual void OnExit(ComponentBase* com) = 0;
};
