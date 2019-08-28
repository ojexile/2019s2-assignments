#include "Behaviour.h"

Behaviour::Behaviour(State* InitialState, AIState* c, AIState* w,
	AIState* i)
{
	m_CurrentState = InitialState;
	m_bStarted = false;
	m_CombatState = c;
	m_WanderState = w;
	m_IdleState = i;
}

Behaviour::Behaviour(Behaviour & ref)
{
	m_Com = nullptr;
	m_CurrentState = ref.m_CurrentState;
	m_bStarted = false;

	m_CombatState = ref.GetCombatState();
	m_WanderState = ref.GetWanderState();
	m_IdleState = ref.GetIdleState();
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
		state->OnEnter(m_Com);
		m_CurrentState->OnExit(m_Com);
		m_CurrentState = state;
		m_CurrentState->OnEnter(m_Com);
	}
}

AIState * Behaviour::GetCombatState()
{
	return m_CombatState;
}

AIState * Behaviour::GetWanderState()
{
	return m_WanderState;
}

AIState * Behaviour::GetIdleState()
{
	return m_IdleState;
}