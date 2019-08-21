#pragma once
#include "Singleton.h"
#include <map>
#include "Vector3.h"
#include "irrKlang.h"
class AudioManager : public Singleton<AudioManager>
{
private:

	std::map<std::string, irrklang::ISound*> currentBGMTracks;
	std::map<std::string, std::pair<float, float>> fadeCommands;
	std::map<std::string, float> m_cooldowns;
public:
	AudioManager();
	~AudioManager();
	void PlayBGM(std::string filePath, std::string ref = "main_bgm");
	void SetBGMVolume(float m, std::string ref = "main_bgm");
	void StopBGM(std::string ref = "main_bgm");
	void QueueFade(float volume, float rate, std::string ref = "main_bgm");
	void Play2D(std::string filePath);
	void Play3D(std::string filePath, Vector3 position);
	void Play3DWithCooldown(std::string filePath, Vector3 position, float cooldown);
	void UpdateListener(Vector3, Vector3);
	void UpdateFading(double dt);
private:
	irrklang::ISoundEngine* engine;
};
