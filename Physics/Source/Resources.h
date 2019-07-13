#pragma once
#include <string>
#include <fstream>
class Resources
{
private:
public:
	const std::string m_ContentPath;
	const std::string m_ObjectPath;
	const std::string m_TexturePath;
	const std::string m_AudioPath;
	const std::string m_ShaderPath;
	const std::string m_HeightMapPath;
	//--------------------------------------------------------------------------------
	Resources(std::string, std::string, std::string, std::string, std::string, std::string);
	~Resources();
};
