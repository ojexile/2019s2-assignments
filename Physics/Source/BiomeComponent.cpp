#include "BiomeComponent.h"

BiomeComponent::BiomeComponent()
	:
	m_biomeType(BIOME_FLAT)
{
}

BiomeComponent::BiomeComponent(eBiomeTypes biomeType = BIOME_FLAT)
	:
	m_biomeType(BIOME_FLAT)
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

std::string BiomeComponent::AppendBiomeToTextureName(std::string s, eBiomeTypes biomeType)
{
	std::string s1;
	switch (biomeType)
	{
	case BIOME_PLAINS:
		s1 = s + "PLAINS";
		break;

	case BIOME_DEFAULT: // for defaults use name as-is
	default:
		s1 = s; 
		break;
	}
	return s1;
}
