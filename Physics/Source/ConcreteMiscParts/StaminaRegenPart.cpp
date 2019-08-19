#include "StaminaRegenPart.h"
#include "../PlayerScript.h"
#include "../WeaponScript.h"
#include "../Stats.h"

StaminaRegenPart::StaminaRegenPart(float SpreadDebuff, float FireRateDebuff, int MaxMagazineDebuff, int MaxAmmoDebuff, float durability)
	: MiscellaneousPartScript(SpreadDebuff, FireRateDebuff, MaxMagazineDebuff, MaxAmmoDebuff, durability)
{
	RYAN_LOG("Stamina Obj created");
}

StaminaRegenPart::~StaminaRegenPart()
{
}

void StaminaRegenPart::Effect()
{
	Buff(false);
	Debuff(false);
}

void StaminaRegenPart::RevertEffect()
{
	Buff(true);
	Debuff(true);
}

void StaminaRegenPart::Buff(bool reverse)
{
	if (!m_PlayerRef)
	{
		RYAN_LOG("PLAYER NOT LINKED");
		return;
	}

	if (!reverse)
	{
		switch (m_SlotType)
		{
		case PartScript::SCOPE:
		{
			// m_PlayerRef->AdjustMaxStamina(20.f, true);
			m_PlayerRef->GetComponent<PlayerScript>()->GetAdditionalStats()->AffectMaxStamina(1.5f);
			break;
		}
		case PartScript::MUZZLE:
		{
			// m_PlayerRef->AdjustMaxStamina(50.f, true);
			m_PlayerRef->GetComponent<PlayerScript>()->GetAdditionalStats()->AffectMaxStamina(1.2f);
			break;
		}
		case PartScript::CLIP:
		{
			// m_PlayerRef->AdjustStaminaRegenRate(10.f, true);
			m_PlayerRef->GetComponent<PlayerScript>()->GetAdditionalStats()->AffectStaminaRegenRate(0.5f);
			break;
		}
		case PartScript::GRIP:
		{
			// m_PlayerRef->AdjustStaminaRegenRate(20.f, true);
			m_PlayerRef->GetComponent<PlayerScript>()->GetAdditionalStats()->AffectStaminaRegenRate(2.5f);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
		switch (m_SlotType)
		{
		case PartScript::SCOPE:
		{
			// m_PlayerRef->AdjustMaxStamina(20.f, true);
			m_PlayerRef->GetComponent<PlayerScript>()->GetAdditionalStats()->AffectMaxStamina(1.f / 1.5f);
			break;
		}
		case PartScript::MUZZLE:
		{
			// m_PlayerRef->AdjustMaxStamina(50.f, true);
			m_PlayerRef->GetComponent<PlayerScript>()->GetAdditionalStats()->AffectMaxStamina(1.f / 1.2f);
			break;
		}
		case PartScript::CLIP:
		{
			// m_PlayerRef->AdjustStaminaRegenRate(10.f, true);
			m_PlayerRef->GetComponent<PlayerScript>()->GetAdditionalStats()->AffectStaminaRegenRate(1.f / 0.5f);
			break;
		}
		case PartScript::GRIP:
		{
			// m_PlayerRef->AdjustStaminaRegenRate(20.f, true);
			m_PlayerRef->GetComponent<PlayerScript>()->GetAdditionalStats()->AffectStaminaRegenRate(1.f / 2.5f);
			break;
		}
		default:
		{
			break;
		}
		}
	}
}

void StaminaRegenPart::Debuff(bool reverse)
{
	if (!m_GunRef)
	{
		RYAN_LOG("GUN NOT LINKED");
		return;
	}

	if (!reverse)
	{
		switch (m_SlotType)
		{
		case PartScript::SCOPE:
		{
			m_GunRef->GUN->SetBulletSpread(m_GunRef->GUN->GetBulletSpread() * m_fSpreadDebuff);
			break;
		}
		case PartScript::MUZZLE:
		{
			m_GunRef->GUN->SetFireRate(m_GunRef->GUN->GetFireRate() * m_fFireRateDebuff);
			break;
		}
		case PartScript::CLIP:
		{
			m_GunRef->GUN->SetMaxMagazineRounds(m_GunRef->GUN->GetMaxMagazineRounds() - m_iMaxMagazineDebuff);
			break;
		}
		case PartScript::GRIP:
		{
			m_GunRef->GUN->SetBulletSpread(m_GunRef->GUN->GetBulletSpread() * m_fSpreadDebuff);
			break;
		}
		default:
		{
			break;
		}
		}
	}
	else
	{
		switch (m_SlotType)
		{
		case PartScript::SCOPE:
		{
			m_GunRef->GUN->SetBulletSpread(m_GunRef->GUN->GetBulletSpread() / m_fSpreadDebuff);
			break;
		}
		case PartScript::MUZZLE:
		{
			m_GunRef->GUN->SetFireRate(m_GunRef->GUN->GetFireRate() / m_fFireRateDebuff);
			break;
		}
		case PartScript::CLIP:
		{
			m_GunRef->GUN->SetMaxMagazineRounds(m_GunRef->GUN->GetMaxMagazineRounds() + m_iMaxMagazineDebuff);
			break;
		}
		case PartScript::GRIP:
		{
			m_GunRef->GUN->SetBulletSpread(m_GunRef->GUN->GetBulletSpread() / m_fSpreadDebuff);
			break;
		}
		default:
		{
			break;
		}
		}
	}
}