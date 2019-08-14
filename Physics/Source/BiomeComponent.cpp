#include "BiomeComponent.h"



BiomeComponent::BiomeComponent(eBiomeTypes biomeType = BIOME_FLAT)
	:
	m_biomeType(biomeType)
{
}

BiomeComponent::~BiomeComponent()
{
}

BiomeComponent::BiomeComponent(BiomeComponent & com)
{
}

void BiomeComponent::Update(double dt)
{
}

BiomeComponent::eBiomeTypes BiomeComponent::GetBiomeType()
{
	return m_biomeType;
}

void BiomeComponent::SetBiomeType(BiomeComponent::eBiomeTypes biomeType)
{
	this->m_biomeType = biomeType;
	return;
}

