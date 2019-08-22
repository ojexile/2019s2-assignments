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

	}
	currentBGMTracks[ref] = sound;
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
	}
}

void AudioManager::QueueFade(float volume, float rate, std::string ref)
{
	fadeCommands[ref] = std::make_pair(volume, rate);
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
void AudioManager::Play3DWithCooldown(std::string filePath, Vector3 position, float cooldown)
{
	if (!engine)
		return;
	if (m_cooldowns.count(filePath) == 0 || m_cooldowns[filePath] < 0)
	{
		m_cooldowns[filePath] = cooldown;
		filePath = Resources::Path::Audio + filePath;
		float fVolume = std::stof(Preferences::GetPref(Resources::PreferencesTerm::AudioVolume));
		engine->play3D(filePath.c_str(), irrklang::vec3df(position.x, position.y, position.z), false, false, false, irrklang::ESM_AUTO_DETECT, true);
	}
}
void AudioManager::UpdateListener(Vector3 p, Vector3 l)
{
	engine->setListenerPosition(irrklang::vec3df(p.x, p.y, p.z), irrklang::vec3df(-l.x, -l.y, -l.z) * 2);
}

void AudioManager::UpdateFading(double dt)
{
	for (auto it = fadeCommands.begin(); it != fadeCommands.end(); ++it)
	{
		float prevVol = currentBGMTracks[it->first]->getVolume();
		float diff = it->second.second * dt;
		if (prevVol > it->second.first) diff *= -1;
		if (signbit(prevVol - it->second.first) != signbit(prevVol + diff - it->second.first))
		{
			currentBGMTracks[it->first]->setVolume(it->second.first);
		}
		else
			currentBGMTracks[it->first]->setVolume(prevVol + diff);
	}
	for (auto it = fadeCommands.begin(); it != fadeCommands.end(); ++it)
	{
		if (currentBGMTracks[it->first]->getVolume() == it->second.first)
		{
			fadeCommands.erase(it->first);
			break;
		}
	}
	for (auto it = m_cooldowns.begin(); it != m_cooldowns.end(); ++it)
		it->second += dt;
}