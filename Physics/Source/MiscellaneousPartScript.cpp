#include "MiscellaneousPartScript.h"



MiscellaneousPartScript::MiscellaneousPartScript(float SpreadDebuff, float FireRateDebuff, int MaxMagazineDebuff, int MaxAmmoDebuff, float durability)
	: PartScript(PART_TYPE::MISC, SLOT_TYPE::ALL, 0.f, durability)
	, m_PlayerRef(nullptr)
	, m_GunRef(nullptr)
	, m_fSpreadDebuff(SpreadDebuff)
	, m_fFireRateDebuff(FireRateDebuff)
	, m_iMaxAmmoDebuff(MaxAmmoDebuff)
	, m_iMaxMagazineDebuff(MaxMagazineDebuff)

{
}


MiscellaneousPartScript::~MiscellaneousPartScript()
{
}

void MiscellaneousPartScript::SetGunReference(GameObject* ref)
{
	this->m_GunRef = ref;
}

void MiscellaneousPartScript::SetPlayerReference(ComponentBase* ref)
{
	this->m_PlayerRef = ref;
}

std::string MiscellaneousPartScript::getName()
{
	return m_Name;
}

void MiscellaneousPartScript::Effect()
{

}