#include "ResourceHandler.h"
#include "Locator.h"
#define RESOURCE_FILE_PATH "resources.dat"
ResourceHandler::ResourceHandler()
{
	m_Res = nullptr;
}

ResourceHandler::~ResourceHandler()
{
}
Resources* ResourceHandler::GetResources()
{
	if (!m_Res)
		InitResources();
	return m_Res;
}
void ResourceHandler::InitResources()
{
	std::ifstream ResouceFile(RESOURCE_FILE_PATH);
	if (!ResouceFile.is_open())
	{
		DEFAULT_LOG("Missing resources file");
		__debugbreak();
	}
	std::string ContentPath;
	std::string ObjectPath;
	std::string TexturePath;
	std::string AudioPath;
	std::string ShaderPath;
	std::string HeightMapPath;
	std::string sLine;
	while (std::getline(ResouceFile, sLine))
	{
		// remove spaces
		for (unsigned i = 0; i < sLine.size(); ++i)
		{
			if (sLine[i] == ' ')
			{
				sLine.erase(i, 1);
				--i;
			}
		}
		std::string sTerm = sLine.substr(0, sLine.find("=", 0));
		std::string sVal = sLine.substr(sLine.find("=", 0) + 1);

		if (sTerm == "ContentPath")
		{
			ContentPath = sVal;
			continue;
		}

		if (sTerm == "ObjectPath")
		{
			ObjectPath = ContentPath + sVal;
			continue;
		}

		if (sTerm == "TexturePath")
		{
			TexturePath = ContentPath + sVal;
			continue;
		}

		if (sTerm == "AudioPath")
		{
			AudioPath = ContentPath + sVal;
			continue;
		}
		if (sTerm == "ShaderPath")
		{
			ShaderPath = ContentPath + sVal;
			continue;
		}
		if (sTerm == "HeightMapPath")
		{
			HeightMapPath = ContentPath + sVal;
			continue;
		}
		DEFAULT_LOG("Unknown resouce data of: " + sTerm + " " + sVal);
	}
	m_Res = new Resources(ContentPath, ObjectPath, TexturePath, AudioPath, ShaderPath, HeightMapPath);
}