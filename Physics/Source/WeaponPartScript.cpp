#include "WeaponPartScript.h"



WeaponPartScript::WeaponPartScript(SLOT_TYPE slot, float Multiplier, float durability, bool isAttached)
	: PartScript(PART_TYPE::WEAPON, slot, Multiplier, durability)
{

}


WeaponPartScript::~WeaponPartScript()
{
}

void WeaponPartScript::Effect()
{
}