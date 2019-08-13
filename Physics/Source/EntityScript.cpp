#include "EntityScript.h"



EntityScript::EntityScript()
{
	m_fMoveForce = 300;
	m_fMaxSpeed = 1;
	m_bInitialised = false;
}
EntityScript::~EntityScript()
{
}
void EntityScript::Init()
{
	m_RB = RIGID;
}
void EntityScript::CheckInit()
{
	if (!m_bInitialised)
	{
		Init();
	}
}
void EntityScript::Log()
{
	DEFAULT_LOG("No rigidbody attached to entity.");
}
bool EntityScript::CheckRB()
{
	if (!m_RB)
	{
		Log();
		return false;
	}
	return true;
}
void EntityScript::Move(Vector3 vDir)
{
	CheckInit();
	if (!CheckRB())
		return;
	m_RB->AddForce(vDir * m_fMoveForce);
	m_RB->ClampVelXZ(m_fMaxSpeed);
}