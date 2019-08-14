#include "WeaponPartScript.h"



WeaponPartScript::WeaponPartScript(SLOT_TYPE slot, double Multiplier, float durability, bool isAttached)
	: PartScript(PART_TYPE::WEAPON, slot, Multiplier, isAttached, durability)
{

}


WeaponPartScript::~WeaponPartScript()
{
}

void WeaponPartScript::Effect()
{

}