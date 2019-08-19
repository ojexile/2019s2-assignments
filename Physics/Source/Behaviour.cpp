#include "Behaviour.h"



Behaviour::Behaviour(State* InitialState)
{
	m_CurrentState = InitialState;
	m_bStarted = false;
}

Behaviour::Behaviour(Behaviour & ref)
{
	m_Com = nullptr;
	m_CurrentState = ref.m_CurrentState->Clone();
	m_bStarted = false;
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
	if (!m_bStarted)
	{
		m_bStarted = true;
		m_CurrentState->OnEnter(m_Com);
	}
	State* state = m_CurrentState->HandleState(m_Com);
	if (state && state != m_CurrentState)
	{
		m_CurrentState->OnExit(m_Com);
		delete m_CurrentState;
		m_CurrentState = state;
		m_CurrentState->OnEnter(m_Com);
	}
}
