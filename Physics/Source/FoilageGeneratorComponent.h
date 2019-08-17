#pragma once
#include "ComponentBase.h"
#include "BiomeComponent.h"

/*
author: lorenzo yanga
desc: base class for foilage generation in chunks. to be used in conjunction with chunks and the biome script
*/

class FoilageGeneratorComponent : public Component
{
	// when the chunk is created, the FGcomp will trigger.
	/*
	determine the density of foilage spawned
	randomise the foilage transformation x times
		lock position by the tile, rotation, (and maybe scale)
		for every time, create a gameobject (using MeshBiomed) and randomly pick the model used (from preset).
		attach to the chunk as a child object
	*/
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
