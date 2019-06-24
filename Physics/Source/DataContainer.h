#pragma once

#include "Mesh.h"
#include "MeshBuilder.h"
#include "Singleton.h"
#include <map>
#include <string>

#include "MeshBuilder.h"

class DataContainer : public Singleton<DataContainer>
{
private:
	std::map<std::string, Mesh*> m_map_Meshes;
public:
	DataContainer();
	~DataContainer();

	Mesh* GetMesh(std::string name);
};
