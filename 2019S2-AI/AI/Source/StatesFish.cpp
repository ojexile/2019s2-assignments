#include "StatesFish.h"

StateTooFull::StateTooFull(const std::string & stateID, GameObject * go)
	: State(stateID),
	m_go(go)
{
}

StateTooFull::~StateTooFull()
{
}

void StateTooFull::Enter()
{
}

void StateTooFull::Update(double dt)
{
}

void StateTooFull::Exit()
{
}
