#include "AudioManager.h"
#include "irrKlang.h"
#include "Resources.h"
#include "Preferences.h"
AudioManager::AudioManager()
{
	engine = irrklang::createIrrKlangDevice();
}

AudioManager::~AudioManager()
{
	engine->drop();
}

void AudioManager::PlayBGM(std::string filePath)
{
	filePath = Resources::Path::Audio + filePath;
	float fVolume = std::stof(Preferences::GetPref(Resources::PreferencesTerm::AudioVolume));
	engine->setSoundVolume(fVolume);
	engine->play2D(filePath.c_str(), true, false, false, irrklang::ESM_AUTO_DETECT, true);
}

void AudioManager::Play3D(std::string filePath, Vector3 position)
{
	filePath = Resources::Path::Audio + filePath;
	engine->play3D(filePath.c_str(), irrklang::vec3df(position.x, position.y, position.z), false, false, false, irrklang::ESM_AUTO_DETECT, true);
}