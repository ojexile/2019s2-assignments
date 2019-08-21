#include "AIEntityScript.h"

AIEntityScript::AIEntityScript(Behaviour* Behaviour, AIState* CombatState)
	: EntityScript(Behaviour)
	, m_CombatState(CombatState)
{
	if (m_Behaviour)
		m_Behaviour->Init(this);
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
	m_bFirstMove = true;
}
AIEntityScript::AIEntityScript(Behaviour* Behaviour, AIState* CombatState, Stats & Stats)
	: EntityScript(Behaviour, Stats)
	, m_CombatState(CombatState)
{
	if (m_Behaviour)
		m_Behaviour->Init(this);
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
	m_bFirstMove = true;
}
AIState * AIEntityScript::GetCombatState()
{
	return m_CombatState;
}
void AIEntityScript::SetTarget(Vector3 v)
{
	m_vTarget = v;
}
void AIEntityScript::MoveToTarget()
{
	// Move towards dir
	if (m_vTarget.IsZero())
		return;
	if (!m_bFirstMove)
	{
		float fBuffer = 2.6f * Time::GetInstance()->GetDeltaTimeF();
		if ((m_vPrevPos - GetPosition()).LengthSquared() < fBuffer * fBuffer)
			Jump();
	}
	else
		m_bFirstMove = false;
	m_vPrevPos = GetPosition();
	RotateTowards(m_vTarget);
	MoveForwards();
}
AIEntityScript::AIEntityScript(AIEntityScript & ref)
	: EntityScript(ref.m_Behaviour, ref.m_BaseStats)
	, m_CombatState(ref.m_CombatState)
{
	m_Values = ref.m_Values;
	m_AdditionalStats = ref.m_AdditionalStats;

	if (ref.m_Behaviour)
	{
		m_Behaviour = new Behaviour(*ref.m_Behaviour);
		m_Behaviour->Init(this);
	}
	else
		m_Behaviour = nullptr;
	m_bInitialised = false;
	m_fAnimStartTime = 0;
	m_bFirstMove = true;
}

AIEntityScript::~AIEntityScript()
{
}

void AIEntityScript::Update(double dt)
{
	EntityScript::Update(dt);
	++m_iCounter;
	if (m_iCounter % 3 == 0)
		UpdateBehaviour();
	MoveToTarget();
}