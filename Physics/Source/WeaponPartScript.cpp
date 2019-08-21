#include "WeaponPartScript.h"



WeaponPartScript::WeaponPartScript(SLOT_TYPE slot, float Multiplier, float durability, bool isAttached)
	: PartScript(slot, Multiplier, durability)
{

}


WeaponPartScript::~WeaponPartScript()
{
}

void WeaponPartScript::Effect()
{
}