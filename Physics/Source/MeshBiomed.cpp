	#include "MeshBiomed.h"
	#include "GL\glew.h"
	#include "Vertex.h"

	#include "Locator.h"
	#include "DataContainer.h"

MeshBiomed::MeshBiomed(const std::string & meshName)
	:
	Mesh(meshName)

{
	for (int i = 0; i < MAX_BIOMES; i++)
	{
		for (int j = 0; j < MAX_TEXTURES; j++)
		{
			m_uBiomedTextureArray[i][j] = 0;
		}
		m_iNumBiomedTextures[i] = 0;
	}
}

MeshBiomed::~MeshBiomed()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	for (int i = 0; i < MAX_BIOMES; ++i)
	{
		for (int j = 0; j < MAX_TEXTURES; ++j)
		{
			glDeleteTextures(1, &m_uBiomedTextureArray[i][j]);
		}
		m_iNumBiomedTextures[i] = NULL;
	}
}

MeshBiomed * MeshBiomed::AddTexture(unsigned i, BiomeComponent::eBiomeTypes e)
{
	if (m_iNumBiomedTextures[e] >= 8)
	{
		DEFAULT_LOG("Max Textures reached.");
		return this;
	}
	m_uBiomedTextureArray[e][m_iNumBiomedTextures[e]] = i;
	++m_iNumBiomedTextures[e];
	return this;
}

MeshBiomed * MeshBiomed::AddTexture(std::string s, BiomeComponent::eBiomeTypes e)
{
	if (m_iNumBiomedTextures[e] >= 8)
	{
		DEFAULT_LOG("Max Textures reached.");
		return this;
	}

	m_uBiomedTextureArray[e][m_iNumBiomedTextures[e]] = DataContainer::GetInstance()->GetTexture(s);
	++m_iNumBiomedTextures[e];
	return this;
}

