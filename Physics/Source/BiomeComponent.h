#pragma once
#include "ComponentBase.h"

class BiomeComponent : public ComponentBase
{

public:
	enum eBiomeTypes
	{
		BIOME_FLAT,
		BIOME_PLAINS
	};
private:
	eBiomeTypes m_biomeType;

public:
	BiomeComponent();
	virtual ~BiomeComponent();
	BiomeComponent(BiomeComponent& com);

	virtual void Update(double dt);

	virtual BiomeComponent* Clone()
	{
		return new BiomeComponent(*this);
	}

	eBiomeTypes GetBiomeType();
	void SetBiomeType(eBiomeTypes biomeType);
};