#include "MiscellaneousPartScript.h"



MiscellaneousPartScript::MiscellaneousPartScript(SLOT_TYPE slot, double Multiplier, float durability)
	: PartScript(PART_TYPE::MISC, slot, Multiplier, durability),
	  m_AttachedSlotType(SLOT_TYPE::ALL)
{
}


MiscellaneousPartScript::~MiscellaneousPartScript()
{
}


void MiscellaneousPartScript::SetAttachment(MiscellaneousPartScript::SLOT_TYPE AttachedSlot)
{
	this->m_AttachedSlotType = AttachedSlot;
}

void MiscellaneousPartScript::Effect()
{

}
