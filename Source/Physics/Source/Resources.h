#pragma once
#include <string>

namespace Resources
{
	namespace Path
	{
		extern const std::string Content;
		extern const std::string Texture;
		extern const std::string Object;
		extern const std::string Audio;
		extern const std::string Shader;
		extern const std::string HeightMap;
		extern const std::string Preferences;
		extern const std::string Keybinds;
		extern const std::string SaveData;
	}

	namespace PreferencesTerm
	{
		extern const std::string WindowSize;
		extern const std::string ConsoleSize;
		extern const std::string WindowPosition;
		extern const std::string ConsolePosition;
		extern const std::string FontSize;
		extern const std::string AudioVolume;
		extern const std::string LogUpdateRate;
		extern const std::string LogUser;
		extern const std::string Quality;
		extern const std::string CamDist;
	}
	namespace Defaults
	{
		extern const float fAmbient;
		extern const float fDiffuse;
		extern const float fSpecular;
		extern const float fShininess;
	}
}