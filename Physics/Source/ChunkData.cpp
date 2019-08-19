#include "ChunkData.h"
#include "MeshBuilder.h"
#include "ChunkEvent.h"

ChunkData::ChunkData(const std::string fileName, int rotate)
{
	m_event = new ChunkEvent(this);
	FILE* file = fopen(fileName.c_str(), "r");
	m_iXSize = fgetc(file);
	m_iYSize = fgetc(file);
	m_iZSize = fgetc(file);
	unsigned int xSizeInBlocks = m_iXSize << 4;
	unsigned int zSizeInBlocks = m_iZSize << 4;
	for (int i = 0; i < m_iXSize * m_iZSize; ++i)
	{
		m_chunkConnections[Vector3(i % m_iXSize, i / m_iXSize)][0] = 0;
		m_chunkConnections[Vector3(i % m_iXSize, i / m_iXSize)][1] = 0;
		m_chunkConnections[Vector3(i % m_iXSize, i / m_iXSize)][2] = 0;
		m_chunkConnections[Vector3(i % m_iXSize, i / m_iXSize)][3] = 0;
	}
	std::vector<unsigned short> blocks_2;
	for (int i = 0; i < xSizeInBlocks * zSizeInBlocks * m_iYSize; ++i)
	{
		int k = fgetc(file);
		int l = fgetc(file);
		blocks_2.push_back(k << 8 | l);
	}
	if (rotate == 0) m_blocks = blocks_2;
	else if (rotate == 3)
	{
		for (int y = 0; y < m_iYSize; ++y)
		{
			for (int x = 0; x < xSizeInBlocks; ++x)
			{
				for (int z = zSizeInBlocks - 1; z >= 0; --z)
				{
					m_blocks.push_back(blocks_2[x + z * xSizeInBlocks + y * xSizeInBlocks * zSizeInBlocks]);
				}
			}
		}
		int k = m_iXSize;
		m_iXSize = m_iZSize;
		m_iZSize = k;
	}
	else if (rotate == 2)
	{
		for (int y = 0; y < m_iYSize; ++y)
		{
			for (int z = zSizeInBlocks - 1; z >= 0; --z)
			{
				for (int x = xSizeInBlocks - 1; x >= 0; --x)
				{
					m_blocks.push_back(blocks_2[x + z * xSizeInBlocks + y * xSizeInBlocks * zSizeInBlocks]);
				}
			}
		}
	}
	else if (rotate == 1)
	{
		for (int y = 0; y < m_iYSize; ++y)
		{
			for (int x = xSizeInBlocks - 1; x >= 0; --x)
			{
				for (int z = 0; z < zSizeInBlocks; ++z)
				{
					m_blocks.push_back(blocks_2[x + z * xSizeInBlocks + y * xSizeInBlocks * zSizeInBlocks]);
				}
			}
		}
		int k = m_iXSize;
		m_iXSize = m_iZSize;
		m_iZSize = k;
	}
	int j = fgetc(file);
	if (j == EOF) return;
	j = fgetc(file);
	for (int i = 0; i < j; ++i)
	{
		int x = fgetc(file);
		int z = fgetc(file);
		int dir = fgetc(file);
		int k = fgetc(file);
		int l = fgetc(file);
		m_chunkConnections[Vector3(x, z)][(dir + rotate) % 4] = k << 8 | l;
	}
	j = fgetc(file);
	if (j == EOF) return;
	for (int i = 0; i < BiomeComponent::BIOME_COUNT; ++i)
	{
		m_validBiomes[static_cast<BiomeComponent::eBiomeTypes>(i)] = false;
	}
	for (int i = 0; i < j; ++i)
	{
		m_validBiomes[static_cast<BiomeComponent::eBiomeTypes>(fgetc(file))] = true;
	}
}

ChunkData::~ChunkData()
{

}

bool ChunkData::IsSolid(Vector3 pos)
{
	int x = (int)pos.x;
	int y = (int)pos.y;
	int z = (int)pos.z;
	if (x < 0 || x >= m_iXSize * 16 || y < 0 || y >= m_iYSize || z < 0 || z >= m_iZSize* 16) return false;
	return m_blocks[x + z * m_iXSize * 16 + y * m_iXSize * m_iZSize * 256] != 0;
}

Vector3 ChunkData::GetSize()
{
	return Vector3(m_iXSize * 16, m_iYSize, m_iZSize * 16);
}

unsigned short ChunkData::GetChunkConnection(Vector3 coords, unsigned char dir)
{
	return m_chunkConnections[coords][dir];
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

MeshBiomed* ChunkData::GenerateMeshBiomed()
{
	MeshBiomed* mesh = dynamic_cast<MeshBiomed*>(MeshBuilder::GenerateChunk("chunk", m_iXSize, m_iYSize, m_iZSize, &m_blocks, true));
	// mesh->AddTexture("terrainflat", BiomeComponent::BIOME_FLAT);
	mesh->AddTexture("Colors", BiomeComponent::BIOME_PLAINS);
	mesh->AddTexture("snow", BiomeComponent::BIOME_SNOW);
	mesh->AddTexture("beachy", BiomeComponent::BIOME_BEACHY);
	mesh->AddTexture("gb", BiomeComponent::BIOME_GAMEBOY);
	mesh->AddTexture("mesa", BiomeComponent::BIOME_MESA);
	mesh->AddTexture("crimson", BiomeComponent::BIOME_CRIMSON);
	mesh->AddTexture("void", BiomeComponent::BIOME_VOID);
	mesh->AddTexture("gray", BiomeComponent::BIOME_MONOCHROME);


	return mesh;
}

Vector3 ChunkData::GetGroundPosition(Vector3 in)
{
	for (int i = 0; i < m_iYSize; i++)
	{
		if (!IsSolid(Vector3(in.x, i, in.z))) return Vector3(in.x, i, in.z);
	}
}

ChunkEvent* ChunkData::GetEvent()
{
	return m_event;
}