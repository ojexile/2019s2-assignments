#include "MiscellaneousPartScript.h"



MiscellaneousPartScript::MiscellaneousPartScript(double Multiplier, float durability)
	: PartScript(PART_TYPE::MISC, SLOT_TYPE::ALL, Multiplier, durability)
	, m_PlayerRef(nullptr)
	, m_GunRef(nullptr)
{
}


MiscellaneousPartScript::~MiscellaneousPartScript()
{
}

void MiscellaneousPartScript::SetGunReference(GameObject* ref)
{
	m_GunRef = ref;
	RYAN_LOG("Gun Set");
}

void MiscellaneousPartScript::SetPlayerReference(PlayerStatsScript* ref)
{
	m_PlayerRef = ref;
	RYAN_LOG("Player Set");
}

std::string MiscellaneousPartScript::getName()
{
	return m_Name;
}

void MiscellaneousPartScript::Effect()
{

}