#include "Behaviour.h"



Behaviour::Behaviour(State* InitialState)
{
	m_CurrentState = InitialState;
	m_bStated = false;
}


void Behaviour::Init(ComponentBase * com)
{
	m_Com = com;
}

Behaviour::~Behaviour()
{
}

void Behaviour::Update()
{
	if (!m_CurrentState)
		return;
	if (!m_bStated)
	{
		m_bStated = true;
		m_CurrentState->OnEnter(m_Com);
	}
	State* state = m_CurrentState->HandleState(m_Com);
	if (state && state != m_CurrentState)
	{
		m_CurrentState->OnExit(m_Com);
		state->OnEnter(m_Com);
		delete m_CurrentState;
		m_CurrentState = state;
	}
}
