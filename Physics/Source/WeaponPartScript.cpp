#include "WeaponPartScript.h"



WeaponPartScript::WeaponPartScript(SLOT_TYPE slot, double Multiplier, float durability)
	: PartScript(PART_TYPE::WEAPON, slot, Multiplier, durability)
{

}


WeaponPartScript::~WeaponPartScript()
{
}

void WeaponPartScript::Effect()
{
}