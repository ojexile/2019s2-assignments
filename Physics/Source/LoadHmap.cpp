#include <iostream>
#include <fstream>
#include <sstream>
#include "LoadHmap.h"
#include "Locator.h"

bool LoadHeightMap(const char *file_path, std::vector<unsigned char> &heightMap)
{
	std::ifstream fileStream(file_path, std::ios::binary);
	if (!fileStream.is_open())
	{
		std::stringstream ss;
		ss << "Impossible to open " << file_path << ". Are you in the right directory ?";
		DEFAULT_LOG(ss.str());
		return false;
	}

	fileStream.seekg(0, std::ios::end);
	std::streampos fsize = (unsigned)fileStream.tellg();

	fileStream.seekg(0, std::ios::beg);
	heightMap.resize((unsigned)fsize);
	fileStream.read((char *)&heightMap[0], fsize);

	fileStream.close();
	return true;
}

float ReadHeightMap(std::vector<unsigned char> &heightMap, float x, float z)
{
	if (x < -0.5f || x > 0.5f || z < -0.5f || z > 0.5f)
		return 0;
	if (heightMap.size() == 0)
		return 0;

	unsigned terrainSize = (unsigned)sqrt((double)heightMap.size());

	unsigned zCoord = (unsigned)((z + 0.5f) * terrainSize);
	unsigned xCoord = (unsigned)((x + 0.5f) * terrainSize);

	return (float)heightMap[zCoord * terrainSize + xCoord] / 256.f;
}