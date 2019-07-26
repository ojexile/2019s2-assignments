#pragma once
#include "Singleton.h"
#include <map>
#include "Vector3.h"
#include "irrKlang.h"
class AudioManager : public Singleton<AudioManager>
{
public:
	AudioManager();
	~AudioManager();
	void PlayBGM(std::string filePath);
	void Play3D(std::string filePath, Vector3 position);
	void Play3D(std::string filePath, Vector3 position, float vol);
private:
	irrklang::ISoundEngine* engine;
};
