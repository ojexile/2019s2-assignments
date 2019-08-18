#pragma once
#include "Singleton.h"
#include <map>
#include "Vector3.h"
#include "irrKlang.h"
class AudioManager : public Singleton<AudioManager>
{
public:
	std::map<std::string, irrklang::ISound*> currentBGMTracks;
	AudioManager();
	~AudioManager();
	void PlayBGM(std::string filePath, std::string ref = "main_bgm");
	void SetBGMVolume(float m, std::string ref = "main_bgm");
	void StopBGM(std::string ref = "main_bgm");
	void Play2D(std::string filePath);
	void Play3D(std::string filePath, Vector3 position);
	void Play3D(std::string filePath, Vector3 position, float vol);
	void UpdateListener(Vector3, Vector3);
private:
	irrklang::ISoundEngine* engine;
};
