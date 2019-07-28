#pragma once
#include "ComponentMacros.h"
#include "Mesh.h"
class HeightMapData
{
private:
	Mesh* m_Mesh;
	_heightmap* m_Map;
	Vector3 m_vScale;
	Vector3 m_vPosOffset;
public:
	HeightMapData(Mesh* Mesh, _heightmap* map, Vector3 vScale, Vector3 PosOffset);
	~HeightMapData();

	Mesh* GetMesh();
	_heightmap* GetHeightMap();
	Vector3 GetScale();
	Vector3 GetPos();
};
