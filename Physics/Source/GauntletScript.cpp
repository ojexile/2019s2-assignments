#include "GauntletScript.h"
#include "MeshController.h"
#include "WorldValues.h"
#include "Time.h"
GauntletScript::GauntletScript()
{
	m_eStone = NONE;
	m_MC = nullptr;
	m_bInUse = false;
	m_fStartTime = 0;
	m_fDuration = 0;
}

GauntletScript::~GauntletScript()
{
}
void GauntletScript::Start()
{
	m_MC = GetComponent<MeshController<Mesh>>();
}
void GauntletScript::Update(double dt)
{
	if (m_bInUse)
	{
		if (Time::GetInstance()->GetElapsedTimeF() > m_fStartTime + m_fDuration)
		{
			StopUse();
			m_fStartTime = 0;
			m_fDuration = 0;
		}
	}
}
void GauntletScript::RotateForward()
{
	if (m_bInUse)
		return;
	switch (m_eStone)
	{
	case NONE:
		m_MC->SetMesh("GauntSoul");
		break;
	case SOUL:
		m_MC->SetMesh("GauntReality");
		break;
	case REALITY:
		m_MC->SetMesh("GauntSpace");
		break;
	case SPACE:
		m_MC->SetMesh("GauntPower");
		break;
	case POWER:
		m_MC->SetMesh("GauntTime");
		break;
	case TIME:
		m_MC->SetMesh("GauntMind");
		break;
	case MIND:
		m_MC->SetMesh("Gaunt");
		break;
	default:
		break;
	}
	m_eStone = static_cast<eSTONES>((m_eStone + 1) % TOTAL);
}
void GauntletScript::RotateBackward()
{
	if (m_bInUse)
		return;
	switch (m_eStone)
	{
	case NONE:
		m_MC->SetMesh("GauntMind");
		break;
	case SOUL:
		m_MC->SetMesh("Gaunt");
		break;
	case REALITY:
		m_MC->SetMesh("GauntSoul");
		break;
	case SPACE:
		m_MC->SetMesh("GauntReality");
		break;
	case POWER:
		m_MC->SetMesh("GauntSpace");
		break;
	case TIME:
		m_MC->SetMesh("GauntPower");
		break;
	case MIND:
		m_MC->SetMesh("GauntTime");
		break;
	default:
		break;
	}
	m_eStone = static_cast<eSTONES>((m_eStone - 1) % TOTAL);
	if (m_eStone == -1)
		m_eStone = static_cast<eSTONES>(TOTAL - 1);
}
void GauntletScript::Use()
{
	m_MC->SetMesh("GauntFist");
	if (m_bInUse)
		return;
	switch (m_eStone)
	{
	case NONE:
		break;
	case SOUL:
		break;
	case REALITY:
		WorldValues::GravityExponent = 0.f;
		m_fStartTime = Time::GetInstance()->GetElapsedTimeF();
		m_fDuration = 5.f;
		break;
	case SPACE:
		break;
	case POWER:
		break;
	case TIME:
		break;
	case MIND:
		break;
	default:
		break;
	}

	m_bInUse = true;
}
void GauntletScript::StopUse()
{
	m_MC->SetMesh("Gaunt");
	if (!m_bInUse)
		return;
	switch (m_eStone)
	{
	case NONE:
		break;
	case SOUL:
		break;
	case REALITY:
		WorldValues::GravityExponent = 1.f;
		break;
	case SPACE:
		break;
	case POWER:
		break;
	case TIME:
		break;
	case MIND:
		break;
	default:
		break;
	}

	m_bInUse = false;
}