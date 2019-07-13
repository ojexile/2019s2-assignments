#include "Resources.h"

Resources::Resources(std::string ContentPath, std::string ObjectPath, std::string TexturePath, std::string AudioPath, std::string ShaderPath, std::string HeightMap)
	:m_ContentPath(ContentPath), m_ObjectPath(ObjectPath), m_TexturePath(TexturePath), m_AudioPath(AudioPath), m_ShaderPath(ShaderPath), m_HeightMapPath(HeightMap)
{
}

Resources::~Resources()
{
}