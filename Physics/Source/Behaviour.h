#pragma once
#include "State.h"
#include "ComponentBase.h"
class Behaviour
{
private:
	ComponentBase* m_Com;
	State* m_CurrentState;
	bool m_bStated;
public:
	Behaviour(State* InitialState);
	void Init(ComponentBase* com);
	~Behaviour();

	void Update();
};

