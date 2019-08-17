#pragma once
#include "Component.h"
#include <string>
//#include "MeshBiomed.h"

/*
author: lorenzo sayo yanga
description: defines a biometype to a gameobject (e.g. terrain).
			 when rendering, texture used will override the default texture
			 if the biomecomponent exists.
*/
class BiomeComponent : public Component
{
public:
	enum eBiomeTypes
	{
		// BIOME_DEFAULT,
		// BIOME_FLAT,
		BIOME_PLAINS,
		BIOME_SNOW,
		BIOME_BEACHY,

		BIOME_COUNT
	};
private:
	eBiomeTypes m_biomeType;
	//MeshBiomed* m_meshBiomedPtr;

public:
	BiomeComponent(eBiomeTypes biomeType);
	virtual ~BiomeComponent();
	BiomeComponent(BiomeComponent& com);

	virtual void Update(double dt);

	virtual BiomeComponent* Clone()
	{
		return new BiomeComponent(*this);
	}

	eBiomeTypes GetBiomeType();
	void SetBiomeType(eBiomeTypes biomeType);
	//void SetMeshBiomedPointer(MeshBiomed*);
};