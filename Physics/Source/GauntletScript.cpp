#include "GauntletScript.h"
#include "MeshController.h"
GauntletScript::GauntletScript()
{
	m_eStone = NONE;
	m_MC = nullptr;
}

GauntletScript::~GauntletScript()
{
}
void GauntletScript::Start()
{
	MeshController<Mesh>* mc = GetComponent<MeshController<Mesh>>();
}
void GauntletScript::RotateFoward()
{
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
void GauntletScript::Use()
{
	m_MC->SetMesh("GauntFist");
}