#pragma once
#include "ComponentMacros.h"
#include "Mesh.h"
class HeightMapData
{
private:
	Mesh* m_Mesh;
	_heightmap* m_Map;
	Vector3 m_vScale;
public:
	HeightMapData(Mesh* Mesh, _heightmap* map, Vector3 vScale);
	~HeightMapData();

	Mesh* GetMesh();
	_heightmap* GetHeightMap();
	Vector3 GetScale();
};
