#pragma once
#include "ComponentBase.h"
#include "BiomeComponent.h"

/*
author: lorenzo yanga
desc: base class for foilage generation in chunks. to be used in conjunction with chunks and the biome script
*/

class FoilageGeneratorComponent : public ComponentBase
{
private:

public:
	FoilageGeneratorComponent(BiomeComponent::eBiomeTypes biomeType);
	virtual ~FoilageGeneratorComponent();
	FoilageGeneratorComponent(FoilageGeneratorComponent& com);

	virtual void Update(double dt);

	virtual FoilageGeneratorComponent* Clone()
	{
		return new FoilageGeneratorComponent(*this);
	}
};
