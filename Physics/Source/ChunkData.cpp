#include "ChunkData.h"
#include "MeshBuilder.h"

ChunkData::ChunkData(const std::string fileName)
{
	FILE* file = fopen(fileName.c_str(), "r");
	m_iXSize = fgetc(file);
	m_iYSize = fgetc(file);
	m_iZSize = fgetc(file);
	unsigned int xSizeInBlocks = m_iXSize << 4;
	unsigned int zSizeInBlocks = m_iZSize << 4;
	for (int i = 0; i < xSizeInBlocks * zSizeInBlocks * m_iYSize; ++i)
	{
		int k = fgetc(file);
		int l = fgetc(file);
		m_blocks.push_back(k << 8 | l);
	}
}

void PutShort(FILE* f, unsigned short s)
{
	fputc(s >> 8, f);
	fputc(s & 255, f);
}

void ChunkData::WriteToFile(const std::string filename)
{
	FILE* file = fopen(filename.c_str(), "w");
	fputc(m_iXSize, file);
	fputc(m_iYSize, file);
	fputc(m_iZSize, file);
	for (auto bIt = m_blocks.begin(); bIt != m_blocks.end(); ++bIt)
	{
		  PutShort(file, *bIt);
	}
}


std::vector<unsigned short> * ChunkData::GetBlocks()
{
	return &m_blocks;
}

Mesh* ChunkData::GenerateMesh()
{
	Mesh* mesh = MeshBuilder::GenerateChunk("chunk", m_iXSize, m_iYSize, m_iZSize, &m_blocks);
	mesh->AddTexture("Colors");
	return mesh;
}