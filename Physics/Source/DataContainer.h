#pragma once

#include "Mesh.h"
#include "MeshBuilder.h"
#include "Singleton.h"
class DataContainer : public Singleton<DataContainer>
{
private:
public:
	DataContainer();
	~DataContainer();
	Mesh* TestMesh;
};
