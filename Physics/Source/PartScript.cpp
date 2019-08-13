#include "PartScript.h"



PartScript::PartScript()
{
}


PartScript::~PartScript()
{
}


void PartScript::DecreaseDurability(float deltaTime)
{
	if (m_fDurability <= 0.f)
		return;
	m_fDurability = m_fDurability - deltaTime;
}