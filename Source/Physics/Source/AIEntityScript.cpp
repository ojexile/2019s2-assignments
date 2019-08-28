#include "AIEntityScript.h"

AIEntityScript::AIEntityScript(Behaviour* Behaviour)
	: EntityScript(Behaviour)
{
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
	m_bFirstMove = true;
}
AIEntityScript::AIEntityScript(Behaviour* Behaviour, Stats & Stats)
	: EntityScript(Behaviour, Stats)
{
	m_bInitialised = false;
	m_bDamageAnim = false;
	m_fAnimStartTime = -1;
	m_AdditionalStats.SetZero();
	m_AdditionalStats.SetOne();
	m_bFirstMove = true;
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
		float fBuffer = 1.f * Time::GetInstance()->GetDeltaTimeF();
		if ((m_vPrevPos - GetPosition()).LengthSquared() < fBuffer * fBuffer || m_bAgainstWall)
			Jump();
		m_bAgainstWall = false;
	}
	else
		m_bFirstMove = false;
	m_vPrevPos = GetPosition();
	RotateTowards(m_vTarget);
	MoveForwards();
}
AIEntityScript::AIEntityScript(AIEntityScript & ref)
	: EntityScript(ref.m_Behaviour, ref.m_BaseStats)
{
	m_Values = ref.m_Values;
	m_AdditionalStats = ref.m_AdditionalStats;
	m_bInitialised = false;
	m_fAnimStartTime = 0;
	m_bFirstMove = true;
}

AIEntityScript::~AIEntityScript()
{
	// EntityScript::~EntityScript();
}

void AIEntityScript::Update(double dt)
{
	EntityScript::Update(dt);
	++m_iCounter;
	if (m_iCounter % 3 == 0)
		UpdateBehaviour();
	MoveToTarget();
}

void AIEntityScript::SetAgainstWall(bool b)
{
	m_bAgainstWall = b;
}