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
		extern const std::string WindowSize = "windowSize";
		extern const std::string ConsoleSize = "consoleSize";
		extern const std::string WindowPosition = "windowPosition";
		extern const std::string ConsolePosition = "consolePosition";
		extern const std::string FontSize = "fontSize";
		extern const std::string AudioVolume = "audioVolume";
		extern const std::string LogUpdateRate = "logUpdateRate";
		extern const std::string LogUser = "logUser";
	}
}