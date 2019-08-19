#pragma once
#include "State.h"
#include "ComponentBase.h"
class Behaviour
{
private:
	ComponentBase* m_Com;
	State* m_CurrentState;
	bool m_bStarted;
public:
	Behaviour(State* InitialState);
	Behaviour(Behaviour &ref);
	void Init(ComponentBase* com);
	~Behaviour();

	void Update();
};

