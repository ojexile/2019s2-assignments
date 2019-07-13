#include "AudioManager.h"
#include "irrKlang.h"
#include "ResourceHandler.h"
AudioManager::AudioManager()
{
	engine = irrklang::createIrrKlangDevice();
}

AudioManager::~AudioManager()
{
	engine->drop();
}

void AudioManager::PlayBGM(std::string fileName)
{
	Resources& res = *ResourceHandler::GetInstance()->GetResources();
	std::string filePath = res.m_AudioPath + fileName;
	engine->setSoundVolume(0.1f);
	engine->play2D(filePath.c_str(), true, false, false, irrklang::ESM_AUTO_DETECT, true);
}

void AudioManager::Play3D(std::string fileName, Vector3 position)
{
	Resources& res = *ResourceHandler::GetInstance()->GetResources();
	std::string filePath = res.m_AudioPath + fileName;
	engine->play3D(filePath.c_str(), irrklang::vec3df(position.x, position.y, position.z), false, false, false, irrklang::ESM_AUTO_DETECT, true);
}