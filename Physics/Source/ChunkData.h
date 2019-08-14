#pragma once
#include <vector>
#include <string>
#include "Constrain.h"
#include "RenderComponent.h"
class ChunkData
{
	unsigned char m_iXSize, m_iYSize, m_iZSize; // size in units of 16 blocks. y is implicit in size of vector
	std::vector<unsigned short> m_blocks; // vector index x + z * m_iXSize + y * m_iXSize * m_iZSize
	std::vector<std::vector<unsigned short>> m_roofworlds;// vector of vectors of same size defining separate roofworlds
	//std::vector<ChunkFeature> m_features;
public:
	ChunkData();
	~ChunkData();
	ChunkData(const std::string fileName);
	void WriteToFile(const std::string fileName);
	Constrain* GetHeightConstraint();
	Mesh* GenerateMesh();
	std::vector<unsigned short> * GetBlocks();
	bool IsSolid(Vector3 pos);
	Vector3 GetSize();
};