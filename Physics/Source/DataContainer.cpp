#include "DataContainer.h"

DataContainer::DataContainer()
{
	TestMesh = MeshBuilder::GenerateQuad("oof", { 1,1,1 }, 50);
}

DataContainer::~DataContainer()
{
	delete TestMesh;
}