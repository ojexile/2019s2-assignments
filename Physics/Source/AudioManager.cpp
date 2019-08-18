#include "AudioManager.h"
#include "irrKlang.h"
#include "Resources.h"
#include "Preferences.h"
AudioManager::AudioManager()
{
	engine = irrklang::createIrrKlangDevice();
	engine->setListenerPosition(irrklang::vec3df(0, 0, 0), irrklang::vec3df(0, 0, -1));
}

AudioManager::~AudioManager()
{
	if (!engine)
		return;
	engine->drop();
}

void AudioManager::PlayBGM(std::string filePath, std::string ref)
{
	if (!engine)
		return;
	filePath = Resources::Path::Audio + filePath;
	float fVolume = std::stof(Preferences::GetPref(Resources::PreferencesTerm::AudioVolume));
	engine->setSoundVolume(fVolume);
	irrklang::ISound* sound = engine->play2D(filePath.c_str(), true, false, true, irrklang::ESM_AUTO_DETECT, false);
	if (currentBGMTracks.count(ref) != 0)
	{
		currentBGMTracks[ref]->stop();
		currentBGMTracks[ref]->drop();
	 // currentBGMTracks[ref]->roll();

		currentBGMTracks[ref] = sound;
	}
}

void AudioManager::SetBGMVolume(float m, std::string ref)
{
	if (currentBGMTracks.count(ref) != 0)
	{
		currentBGMTracks[ref]->setVolume(m);
	}
}

void AudioManager::StopBGM(std::string ref)
{
	if (currentBGMTracks.count(ref) != 0)
	{
		currentBGMTracks[ref]->stop();
		currentBGMTracks[ref]->drop();
	}
}

void AudioManager::Play2D(std::string filePath)
{
	if (!engine)
		return;
	filePath = Resources::Path::Audio + filePath;
	engine->play2D(filePath.c_str(), false, false, false, irrklang::ESM_AUTO_DETECT, true);

}

void AudioManager::Play3D(std::string filePath, Vector3 position)
{
	if (!engine)
		return;
	filePath = Resources::Path::Audio + filePath;
	engine->play3D(filePath.c_str(), irrklang::vec3df(position.x, position.y, position.z), false, false, false, irrklang::ESM_AUTO_DETECT, true);
}
void AudioManager::Play3D(std::string filePath, Vector3 position, float fVol)
{
	if (!engine)
		return;
	filePath = Resources::Path::Audio + filePath;
	float fVolume = std::stof(Preferences::GetPref(Resources::PreferencesTerm::AudioVolume));
	engine->setSoundVolume(fVol * fVolume);
	engine->play3D(filePath.c_str(), irrklang::vec3df(position.x, position.y, position.z), false, false, false, irrklang::ESM_AUTO_DETECT, true);
}
void AudioManager::UpdateListener(Vector3 p, Vector3 l)
{
	engine->setListenerPosition(irrklang::vec3df(p.x, p.y, p.z), irrklang::vec3df(-l.x, -l.y, -l.z) * 2);
}