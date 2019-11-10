#include "StatesShark.h"

StateCrazy::StateCrazy(const std::string& stateID, GameObject* go)
	: State(stateID), m_go(go)
{
}

StateCrazy::~StateCrazy()
	: State(stateID), m_go(go)
{
}

StateNaughty::StateNaughty(const std::string& stateID, GameObject* go)
	: State(stateID), m_go(go) 
{
}
