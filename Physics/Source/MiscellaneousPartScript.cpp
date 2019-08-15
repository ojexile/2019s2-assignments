#include "MiscellaneousPartScript.h"



MiscellaneousPartScript::MiscellaneousPartScript(SLOT_TYPE slot, double Multiplier, float durability)
	: PartScript(PART_TYPE::MISC, slot, Multiplier, durability),
	  m_AttachedSlotType(SLOT_TYPE::ALL)
{
}


MiscellaneousPartScript::~MiscellaneousPartScript()
{
}

void MiscellaneousPartScript::Effect()
{
	Buff();
	Debuff();
}

void MiscellaneousPartScript::Buff()
{
	switch (m_BuffedStat)
	{
	default:
	{
		break;
	}
	}
}

void MiscellaneousPartScript::Debuff()
{
	switch (m_AttachedSlotType)
	{
	case PartScript::SCOPE:
	{
		break;
	}
	case PartScript::MUZZLE:
	{
		break;
	}
	case PartScript::CLIP:
	{
		break;
	}
	case PartScript::GRIP:
	{
		break;
	}
	default:
	{
		break;
	}
	}
}

void MiscellaneousPartScript::SetAttachment(MiscellaneousPartScript::SLOT_TYPE AttachedSlot)
{
	this->m_AttachedSlotType = AttachedSlot;
}