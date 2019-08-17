#pragma once
#include <vector>
#include <string>
#include "Constrain.h"
#include "RenderComponent.h"
#include "BiomeComponent.h"
class ChunkData
{
	unsigned char m_iXSize, m_iYSize, m_iZSize; // size in units of 16 blocks. y is implicit in size of vector
	std::vector<unsigned short> m_blocks; // vector index x + z * m_iXSize + y * m_iXSize * m_iZSize
	std::vector<std::vector<unsigned short>> m_roofworlds;// vector of vectors of same size defining separate roofworlds
	std::map<Vector3, std::map<unsigned char, unsigned short>> m_chunkConnections;
	std::map<BiomeComponent::eBiomeTypes, bool> m_validBiomes;
	std::vector<int> m_events;
	//std::vector<ChunkFeature> m_features;
public:
	ChunkData(const std::string fileName);
	~ChunkData();
	void WriteToFile(const std::string fileName);
	Mesh* GenerateMesh();
	MeshBiomed* GenerateMeshBiomed();
	std::vector<unsigned short> * GetBlocks();
	bool IsSolid(Vector3 pos);
	Vector3 GetSize();
	unsigned short GetChunkConnection(Vector3 coords, unsigned char dir);
	Vector3 GetGroundPosition(Vector3 coords);
};