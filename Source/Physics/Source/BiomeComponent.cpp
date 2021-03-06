#include "BiomeComponent.h"
#include "RenderComponent.h"

BiomeComponent::BiomeComponent(eBiomeTypes biomeType)
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