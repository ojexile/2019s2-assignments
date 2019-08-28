#include "HeightMapData.h"

HeightMapData::HeightMapData(Mesh* Mesh, _heightmap* Map, Vector3 vScale, Vector3 vPosOffset)
	:m_Mesh(Mesh)
	, m_Map(Map)
	, m_vScale(vScale)
	, m_vPosOffset(vPosOffset)
{
}

HeightMapData::~HeightMapData()
{
	delete m_Map;
	delete m_Mesh;
}
Mesh* HeightMapData::GetMesh()
{
	return m_Mesh;
}

MeshBiomed * HeightMapData::GetMeshBiomed()
{
	return dynamic_cast<MeshBiomed*>(m_Mesh);
}


_heightmap* HeightMapData::GetHeightMap()
{
	return m_Map;
}
Vector3 HeightMapData::GetScale()
{
	return m_vScale;
}
Vector3 HeightMapData::GetPos()
{
	return m_vPosOffset;
}