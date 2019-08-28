#include "MeshBiomed.h"
#include "GL\glew.h"
#include "Vertex.h"

#include "Locator.h"
#include "DataContainer.h"

MeshBiomed::MeshBiomed(const std::string & meshName) : Mesh(meshName)
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
	return; // disable deletion of textures
	for (int i = 0; i < MAX_BIOMES; ++i)
	{
		for (int j = 0; j < MAX_TEXTURES; ++j)
		{
			if (m_uBiomedTextureArray[i][j] != 0)
				glDeleteTextures(1, &m_uBiomedTextureArray[i][j]);
		}
		//m_iNumBiomedTextures[i] = NULL;
	}

	for (int i = 0; i < MAX_TEXTURES; ++i)
	{
		if (m_uTextureArray[i] != 0)
			glDeleteTextures(1, &m_uTextureArray[i]);
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

void MeshBiomed::Render(BiomeComponent::eBiomeTypes type)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	if (m_uBiomedTextureArray[type][0] > 0)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if (mode == DRAW_LINES)
		glDrawElements(GL_LINES, indexSize, GL_UNSIGNED_INT, 0);
	else if (mode == DRAW_TRIANGLE_STRIP)
		glDrawElements(GL_TRIANGLE_STRIP, indexSize, GL_UNSIGNED_INT, 0);
	else
		glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if (m_uBiomedTextureArray[type][0] > 0)
	{
		glDisableVertexAttribArray(3);
	}
}

void MeshBiomed::Render(BiomeComponent::eBiomeTypes type, unsigned offset, unsigned count)
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Position));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color)));
	if (m_uBiomedTextureArray[type][0] > 0)
	{
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(Position) + sizeof(Color) + sizeof(Vector3)));
	}

	//glDrawArrays(GL_TRIANGLES, offset, count);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	if (mode == DRAW_LINES)
		glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	else if (mode == DRAW_TRIANGLE_STRIP)
		glDrawElements(GL_TRIANGLE_STRIP, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));
	else
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (void*)(offset * sizeof(GLuint)));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	if (m_uBiomedTextureArray[type][0] > 0)
	{
		glDisableVertexAttribArray(3);
	}
}