#pragma once
#include "ComponentBase.h"
#include <string> 
//#include "MeshBiomed.h"

/*
author: lorenzo sayo yanga
description: defines a biometype to a gameobject (e.g. terrain). 
			 when rendering, texture used will override the default texture
			 if the biomecomponent exists.
*/
class BiomeComponent : public ComponentBase
{
public:
	enum eBiomeTypes
	{
		BIOME_DEFAULT,
		BIOME_FLAT,
		BIOME_PLAINS,

		BIOME_COUNT
	};
private:
	eBiomeTypes m_biomeType;
	//MeshBiomed* m_meshBiomedPtr;

public:
	BiomeComponent();
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