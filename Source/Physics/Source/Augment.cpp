#include "Augment.h"

Augment::Augment()
	: m_EntityRef(nullptr),
	  m_GunRef(nullptr)
{
	m_AugmentType = NIL;
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

void Augment::SetDescription(std::string s)
{
	m_Description = s;
}

std::string Augment::GetDescription(void)
{
	return m_Description;
}

void Augment::SetName(std::string s)
{
	m_Name = s;
}

std::string Augment::GetName(void)
{
	return m_Name;
}

Augment::eAugmentType Augment::GetAugmentType()
{
	return m_AugmentType;
}