#include "AudioManager.h"
#include "irrKlang.h"

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
	engine->setSoundVolume(0.1);
	engine->play2D(filePath.c_str(), true, false, false, irrklang::ESM_AUTO_DETECT, true);
}

void AudioManager::Play3D(std::string filePath, Vector3 position)
{
	engine->play3D(filePath.c_str(), irrklang::vec3df(position.x, position.y, position.z), false, false, false, irrklang::ESM_AUTO_DETECT, true);
}
