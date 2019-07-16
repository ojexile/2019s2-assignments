#include "Resources.h"
namespace Resources
{
	extern const std::string ContentPath = "content/";
	extern const std::string TexturePath = ContentPath + "textures/";
	extern const  std::string ObjectPath = ContentPath + "objects/";
	extern const std::string AudioPath = ContentPath + "audio/";
	extern const std::string ShaderPath = ContentPath + "shaders/";
	extern const std::string HeightMapPath = ContentPath + "heightMaps/";
	extern const std::string Preferences = ContentPath + "preferences.ini";
	extern const std::string Keybinds = ContentPath + "keybinds.cfg";


	namespace PreferencesTerm
	{
		extern const std::string WindowSize = "WindowSize";
		extern const std::string ConsoleSize = "ConsoleSize";
		extern const std::string WindowPosition = "WindowPosition";
		extern const std::string ConsolePosition = "ConsolePostion";
		extern const std::string FontSize = "FontSize";
		extern const std::string AudioVolume = "AudioVolume";
	}
}