#include "Augment.h"

Augment::Augment()
	: m_EntityRef(nullptr),
	  m_GunRef(nullptr)
{
}


Augment::~Augment()
{
}

void Augment::SetGunReference(ScriptComponent* ref)
{
	m_GunRef = ref;
}

void Augment::SetEntityReference(ScriptComponent* ref)
{
	m_EntityRef = ref;
}

Augment::eAugmentType Augment::GetAugmentType()
{
	return m_AugmentType;
}