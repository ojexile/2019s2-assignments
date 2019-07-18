#include "Resources.h"
namespace Resources
{
	namespace Path
	{
		extern const std::string Content = "content/";
		extern const std::string Texture = Content + "textures/";
		extern const  std::string Object = Content + "objects/";
		extern const std::string Audio = Content + "audio/";
		extern const std::string Shader = Content + "shaders/";
		extern const std::string HeightMap = Content + "heightMaps/";
		extern const std::string Preferences = Content + "preferences.ini";
		extern const std::string Keybinds = Content + "keybinds.cfg";
	}

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