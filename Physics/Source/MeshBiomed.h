#pragma once
#include "BiomeComponent.h"
#include "Mesh.h"
/*
author: lorenzo yanga
desc: child class of Mesh made to support biomecomponent.
*/

#define MAX_BIOMES BiomeComponent::eBiomeTypes::BIOME_COUNT

class MeshBiomed : public Mesh
{
private:
	int m_iNumBiomedTextures[MAX_BIOMES];
	unsigned m_uBiomedTextureArray[MAX_BIOMES][MAX_TEXTURES];
public:
	MeshBiomed(const std::string &meshName);
	//MeshBiomed(Mesh*) //upgradish function
	~MeshBiomed();

	MeshBiomed* AddTexture(unsigned i, BiomeComponent::eBiomeTypes);
	MeshBiomed* AddTexture(std::string s, BiomeComponent::eBiomeTypes);

	virtual void Render(BiomeComponent::eBiomeTypes);
	virtual void Render(BiomeComponent::eBiomeTypes, unsigned offset, unsigned count);

	friend RenderingManagerBase;
};