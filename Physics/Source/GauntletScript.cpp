#include "GauntletScript.h"
#include "MeshController.h"
GauntletScript::GauntletScript()
{
	m_eStone = NONE;
	m_MC = nullptr;
	m_bInUse = false;
}

GauntletScript::~GauntletScript()
{
}
void GauntletScript::Start()
{
	m_MC = GetComponent<MeshController<Mesh>>();
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
	m_bInUse = true;
}